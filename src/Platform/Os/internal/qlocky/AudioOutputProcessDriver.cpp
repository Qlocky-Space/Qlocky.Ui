#include "AudioOutputProcessDriver.h"

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <ng-log/logging.h>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {

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
        std::vector<std::string> commandParts {};
        commandParts.reserve(playerCommand->arguments.size() + 2);
        commandParts.push_back(playerCommand->executable);
        commandParts.insert(commandParts.end(), playerCommand->arguments.begin(), playerCommand->arguments.end());
        commandParts.push_back(source);

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
    if (char const* configuredPlayer = std::getenv("QLOCKY_AUDIO_PLAYER")) {
        std::string const executable {configuredPlayer};
        if (!executable.empty() && isExecutableAvailable(executable)) {
            return PlayerCommand {executable, {}};
        }
    }

    std::vector<PlayerCommand> const supportedPlayers {
        {"gst-play-1.0", {"--no-interactive"}},
        {"ffplay", {"-nodisp", "-autoexit"}},
        {"mpv", {"--no-video"}},
        {"cvlc", {"--intf", "dummy"}},
    };

    for (PlayerCommand const& player : supportedPlayers) {
        if (isExecutableAvailable(player.executable)) {
            return player;
        }
    }

    return std::nullopt;
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
