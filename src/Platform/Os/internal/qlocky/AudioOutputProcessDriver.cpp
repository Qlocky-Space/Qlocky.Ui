#include "AudioOutputProcessDriver.h"

#include <cerrno>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <ng-log/logging.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

constexpr char const* PLAYER_EXECUTABLE_DEFAULT {"/usr/bin/gst-launch-1.0"};
constexpr char const* PLAYER_EXECUTABLE_ENV {"QLOCKY_AUDIO_PLAYER_PATH"};
constexpr char const* PLAYER_COMMAND_NAME {"gst-launch-1.0"};
constexpr char const* PLAYER_PID_FILE_PATH {"/tmp/qlocky-audio-player.pid"};
constexpr char const* BUFFER_DURATION {"buffer-duration=5000000000"}; // 5 seconds in nanoseconds
constexpr char const* BUFFER_SIZE {"buffer-size=4194304"};            // 4 MB in bytes
// TODO Just a rough estimation, shall be tuned and made it configurable. Ensure Min/Max audio volume (See AudioOutputMixer) is adjusted as well.
constexpr char const* EQ_FILTER_ARGUMENT {
    "audio-filter=equalizer-nbands num-bands=31 "
    "band0::gain=0 "
    "band1::gain=0.08 "
    "band2::gain=0.72 "
    "band3::gain=0.72 "
    "band4::gain=-0.88 "
    "band5::gain=-2.4 "
    "band6::gain=-4 "
    "band7::gain=-1.52 "
    "band8::gain=-0.56 "
    "band9::gain=-4.96 "
    "band10::gain=-7.12 "
    "band11::gain=-9.6 "
    "band12::gain=-12.4 "
    "band13::gain=-12.4 "
    "band14::gain=-13.36 "
    "band15::gain=-18.96 "
    "band16::gain=-12.16 "
    "band17::gain=-11.52 "
    "band18::gain=-11.216 "
    "band19::gain=-10.88 "
    "band20::gain=-10.88 "
    "band21::gain=-10.88 "
    "band22::gain=-11.04 "
    "band23::gain=-10.24 "
    "band24::gain=-7.76 "
    "band25::gain=-6.24 "
    "band26::gain=-4.32 "
    "band27::gain=-4.96 "
    "band28::gain=-5.6 "
    "band29::gain=-5.28 "
    "band30::gain=-6.48"};

} // namespace

AudioOutputProcessDriver::AudioOutputProcessDriver() {
    cleanupTrackedPlayer();
}

AudioOutputProcessDriver::~AudioOutputProcessDriver() {
    stop();
    if (m_waitThread.joinable()) {
        m_waitThread.join();
    }
}

AudioOutputResult AudioOutputProcessDriver::play(std::string const& source) {
    if (source.empty()) {
        notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_INVALID_ARGUMENT);
        return AudioOutputResult::error(AudioOutputErrorCode::ERROR_INVALID_ARGUMENT);
    }

    auto const playerCommand = resolvePlayerCommand();
    if (!playerCommand.has_value()) {
        LOG(WARNING) << "No supported OS audio player backend found";
        notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_BACKEND_NOT_AVAILABLE);
        return AudioOutputResult::error(AudioOutputErrorCode::ERROR_BACKEND_NOT_AVAILABLE);
    }

    stop();
    if (m_waitThread.joinable()) {
        m_waitThread.join();
    }

    pid_t const pid = fork();
    if (pid < 0) {
        notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_START_FAILED);
        return AudioOutputResult::error(AudioOutputErrorCode::ERROR_START_FAILED);
    }

    if (pid == 0) {
        std::string const uriArgument = std::string {"uri="} + source;

        std::vector<std::string> commandParts {};
        commandParts.reserve(playerCommand->arguments.size() + 1);
        commandParts.push_back(playerCommand->executable);
        commandParts.insert(commandParts.end(), playerCommand->arguments.begin(), playerCommand->arguments.end());
        commandParts.push_back(uriArgument);

        std::vector<char*> argv {};
        argv.reserve(commandParts.size() + 1);
        for (std::string& part : commandParts) {
            argv.push_back(part.data());
        }
        argv.push_back(nullptr);

        execv(playerCommand->executable.c_str(), argv.data());
        _exit(127);
    }

    {
        std::lock_guard<std::mutex> lock {m_mutex};
        m_playerPid = pid;
        m_playing = true;
        m_currentSource = source;
    }

    storeTrackedPlayerPid(pid);

    m_waitThread = std::thread([this, pid]() {
        waitForPlayer(pid);
    });

    notify(&AudioOutputListenerIfc::onPlaybackStarted, source);
    return AudioOutputResult::success(true);
}

AudioOutputResult AudioOutputProcessDriver::stop() {
    pid_t pidToStop {-1};

    {
        std::lock_guard<std::mutex> lock {m_mutex};
        if (m_playerPid < 0) {
            return AudioOutputResult::success(true);
        }

        pidToStop = m_playerPid;
        m_playerPid = -1;
        m_playing = false;
        m_currentSource.clear();
    }

    if (kill(pidToStop, SIGTERM) != 0 && errno != ESRCH) {
        notify(&AudioOutputListenerIfc::onPlaybackFailed, AudioOutputErrorCode::ERROR_STOP_FAILED);
        return AudioOutputResult::error(AudioOutputErrorCode::ERROR_STOP_FAILED);
    }

    if (m_waitThread.joinable()) {
        m_waitThread.join();
    }

    clearTrackedPlayerPid();

    notify(&AudioOutputListenerIfc::onPlaybackStopped);
    return AudioOutputResult::success(true);
}

bool AudioOutputProcessDriver::isPlaying() const {
    std::lock_guard<std::mutex> lock {m_mutex};
    return m_playing;
}

std::optional<AudioOutputProcessDriver::PlayerCommand> AudioOutputProcessDriver::resolvePlayerCommand() {
    std::string executable {PLAYER_EXECUTABLE_DEFAULT};

    char const* configuredExecutable = std::getenv(PLAYER_EXECUTABLE_ENV);
    if (configuredExecutable != nullptr && configuredExecutable[0] != '\0') {
        std::string const configuredPath {configuredExecutable};
        if (configuredPath.front() != '/') {
            LOG(WARNING) << "Ignoring non-absolute audio player path from " << PLAYER_EXECUTABLE_ENV;
            return std::nullopt;
        }

        executable = configuredPath;
    }

    if (isExecutableAvailable(executable)) {
        return PlayerCommand {executable, {"playbin", BUFFER_DURATION, BUFFER_SIZE, EQ_FILTER_ARGUMENT}};
    }

    return std::nullopt;
}

void AudioOutputProcessDriver::cleanupTrackedPlayer() {
    std::ifstream pidFile {PLAYER_PID_FILE_PATH};
    if (!pidFile.is_open()) {
        return;
    }

    pid_t trackedPid {-1};
    pidFile >> trackedPid;
    if (trackedPid <= 0) {
        clearTrackedPlayerPid();
        return;
    }

    if (kill(trackedPid, 0) != 0) {
        clearTrackedPlayerPid();
        return;
    }

    if (!isTrackedPlayerProcess(trackedPid)) {
        clearTrackedPlayerPid();
        return;
    }

    if (kill(trackedPid, SIGTERM) != 0 && errno != ESRCH) {
        LOG(WARNING) << "Failed to terminate tracked audio player process pid=" << trackedPid;
    }

    clearTrackedPlayerPid();
}

void AudioOutputProcessDriver::storeTrackedPlayerPid(pid_t pid) {
    std::ofstream pidFile {PLAYER_PID_FILE_PATH, std::ios::trunc};
    if (!pidFile.is_open()) {
        LOG(WARNING) << "Failed to write audio player pid file";
        return;
    }

    pidFile << pid;
}

void AudioOutputProcessDriver::clearTrackedPlayerPid() {
    std::remove(PLAYER_PID_FILE_PATH);
}

bool AudioOutputProcessDriver::isTrackedPlayerProcess(pid_t pid) {
    std::ifstream commandFile {std::string {"/proc/"} + std::to_string(pid) + "/comm"};
    if (!commandFile.is_open()) {
        return false;
    }

    std::string commandName {};
    std::getline(commandFile, commandName);
    return commandName == PLAYER_COMMAND_NAME;
}

bool AudioOutputProcessDriver::isExecutableAvailable(std::string const& executable) {
    if (executable.empty() || executable.front() != '/') {
        return false;
    }

    return access(executable.c_str(), X_OK) == 0;
}

void AudioOutputProcessDriver::waitForPlayer(pid_t pid) {
    int status {0};
    waitpid(pid, &status, 0);

    bool notifyStopped {false};
    {
        std::lock_guard<std::mutex> lock {m_mutex};
        if (m_playerPid == pid) {
            m_playerPid = -1;
            m_playing = false;
            m_currentSource.clear();
            notifyStopped = true;
        }
    }

    if (notifyStopped) {
        clearTrackedPlayerPid();
        notify(&AudioOutputListenerIfc::onPlaybackStopped);
    }
}
