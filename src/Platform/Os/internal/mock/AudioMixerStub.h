#ifndef SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_MIXER_STUB_H
#define SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_MIXER_STUB_H

#include <algorithm>
#include <cstdint>
#include <Subject.h>

#include "AudioMixerIfc.h"

class AudioMixerStub final : public Subject<AudioMixerListenerIfc>, public AudioMixerIfc {
public:

    AudioMixerStub() = default;
    ~AudioMixerStub() final = default;

    void attach(AudioMixerListenerIfc* observer) final {
        Subject<AudioMixerListenerIfc>::attach(observer);
    }

    void detach(AudioMixerListenerIfc* observer) final {
        Subject<AudioMixerListenerIfc>::detach(observer);
    }

    bool setOutputVolume(uint8_t volumePercent) final;
    uint8_t outputVolume() const final;

private:

    uint8_t m_volumePercent {100};
};

#endif // SRC_PLATFORM_OS_INTERNAL_MOCK_AUDIO_MIXER_STUB_H
