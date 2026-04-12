#ifndef SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_OUTPUT_STUB_H
#define SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_OUTPUT_STUB_H

#include <string>
#include <Subject.h>

#include "AudioOutputIfc.h"

class AudioOutputStub final : public Subject<AudioOutputListenerIfc>, public AudioOutputIfc {
public:

    AudioOutputStub() = default;
    ~AudioOutputStub() final = default;

    void attach(AudioOutputListenerIfc* observer) final {
        Subject<AudioOutputListenerIfc>::attach(observer);
    }

    void detach(AudioOutputListenerIfc* observer) final {
        Subject<AudioOutputListenerIfc>::detach(observer);
    }

    AudioOutputResult play(std::string const& source) final;
    AudioOutputResult stop() final;
    bool isPlaying() const final {
        return m_playing;
    }

private:

    bool m_playing {false};
    std::string m_currentSource {};
};

#endif // SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_OUTPUT_STUB_H
