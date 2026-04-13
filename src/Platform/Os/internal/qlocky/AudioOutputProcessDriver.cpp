#include "AudioOutputProcessDriver.h"

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <fstream>
#include <ng-log/logging.h>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

constexpr char const* PLAYER_EXECUTABLE {"gst-launch-1.0"};
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

std::vector<std::string> splitPath(std::string const& path) {
    std::vector<std::string> entries {};
    std::stringstream stream {path};
    std::string entry {};
    while (std::getline(stream, entry, ':')) {
        if (!entry.empty()) {
            entries.push_back(entry);
        }
    }

    return entries;
}

} // namespace

AudioOutputProcessDriver::AudioOutputProcessDriver() {
    terminateExistingPlayers();
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
        LOG(WARNING) << "No supported OS audio player backend found in PATH";
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

        execvp(playerCommand->executable.c_str(), argv.data());
        _exit(127);
    }

    {
        std::lock_guard<std::mutex> lock {m_mutex};
        m_playerPid = pid;
        m_playing = true;
        m_currentSource = source;
    }

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

    notify(&AudioOutputListenerIfc::onPlaybackStopped);
    return AudioOutputResult::success(true);
}

bool AudioOutputProcessDriver::isPlaying() const {
    std::lock_guard<std::mutex> lock {m_mutex};
    return m_playing;
}

std::optional<AudioOutputProcessDriver::PlayerCommand> AudioOutputProcessDriver::resolvePlayerCommand() {
    if (isExecutableAvailable(PLAYER_EXECUTABLE)) {
        return PlayerCommand {PLAYER_EXECUTABLE, {"playbin", BUFFER_DURATION, BUFFER_SIZE, EQ_FILTER_ARGUMENT}};
    }

    return std::nullopt;
}

void AudioOutputProcessDriver::terminateExistingPlayers() {
    DIR* procDir {opendir("/proc")};
    if (procDir == nullptr) {
        LOG(WARNING) << "Failed to open /proc for stale audio player cleanup";
        return;
    }

    pid_t const currentPid {getpid()};
    dirent* entry {nullptr};
    while ((entry = readdir(procDir)) != nullptr) {
        char* endPtr {nullptr};
        long const rawPid {std::strtol(entry->d_name, &endPtr, 10)};
        if (endPtr == nullptr || *endPtr != '\0' || rawPid <= 0) {
            continue;
        }

        pid_t const candidatePid {static_cast<pid_t>(rawPid)};
        if (candidatePid == currentPid) {
            continue;
        }

        std::ifstream commandFile {std::string {"/proc/"} + entry->d_name + "/comm"};
        if (!commandFile.is_open()) {
            continue;
        }

        std::string commandName {};
        std::getline(commandFile, commandName);
        if (commandName != PLAYER_EXECUTABLE) {
            continue;
        }

        if (kill(candidatePid, SIGTERM) != 0 && errno != ESRCH) {
            LOG(WARNING) << "Failed to terminate stale audio player process pid=" << candidatePid;
        }
    }

    closedir(procDir);
}

bool AudioOutputProcessDriver::isExecutableAvailable(std::string const& executable) {
    if (executable.find('/') != std::string::npos) {
        return access(executable.c_str(), X_OK) == 0;
    }

    char const* pathEnv = std::getenv("PATH");
    if (pathEnv == nullptr) {
        return false;
    }

    for (std::string const& entry : splitPath(pathEnv)) {
        std::string const candidate = entry + "/" + executable;
        if (access(candidate.c_str(), X_OK) == 0) {
            return true;
        }
    }

    return false;
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
        notify(&AudioOutputListenerIfc::onPlaybackStopped);
    }
}
