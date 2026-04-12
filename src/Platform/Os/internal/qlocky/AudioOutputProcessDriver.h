#ifndef SRC_PLATFORM_OS_INTERNAL_QLOCKY_AUDIO_OUTPUT_PROCESS_DRIVER_H
#define SRC_PLATFORM_OS_INTERNAL_QLOCKY_AUDIO_OUTPUT_PROCESS_DRIVER_H

#include <mutex>
#include <optional>
#include <string>
#include <Subject.h>
#include <sys/types.h>
#include <thread>
#include <vector>

#include "AudioOutputIfc.h"

class AudioOutputProcessDriver final : public Subject<AudioOutputListenerIfc>, public AudioOutputIfc {
public:

    AudioOutputProcessDriver() = default;
    ~AudioOutputProcessDriver() final;

    void attach(AudioOutputListenerIfc* observer) final {
        Subject<AudioOutputListenerIfc>::attach(observer);
    }

    void detach(AudioOutputListenerIfc* observer) final {
        Subject<AudioOutputListenerIfc>::detach(observer);
    }

    AudioOutputResult play(std::string const& source) final;
    AudioOutputResult stop() final;
    bool isPlaying() const final;

private:

    struct PlayerCommand final {
        std::string executable;
        std::vector<std::string> arguments;
    };

    static std::optional<PlayerCommand> resolvePlayerCommand();
    static bool isExecutableAvailable(std::string const& executable);
    void waitForPlayer(pid_t pid);

    mutable std::mutex m_mutex {};
    pid_t m_playerPid {-1};
    bool m_playing {false};
    std::string m_currentSource {};
    std::thread m_waitThread {};
};

#endif // SRC_PLATFORM_OS_INTERNAL_QLOCKY_AUDIO_OUTPUT_PROCESS_DRIVER_H
