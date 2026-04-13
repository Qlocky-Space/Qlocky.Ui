#ifndef SRC_PLATFORM_OS_INTERNAL_QLOCKY_AUDIO_OUTPUT_MIXER_H
#define SRC_PLATFORM_OS_INTERNAL_QLOCKY_AUDIO_OUTPUT_MIXER_H

#include <alsa/asoundlib.h>
#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <Subject.h>
#include <thread>

#include "AudioMixerIfc.h"

/**
 * ALSA-backed audio mixer implementation for qlocky targets.
 */
class AudioOutputMixer final : public Subject<AudioMixerListenerIfc>, public AudioMixerIfc {
public:

    /**
     * Create the audio mixer.
     */
    AudioOutputMixer();

    /**
     * Destroy the audio mixer.
     */
    ~AudioOutputMixer() final;

    /**
     * @see SubjectIfc::attach
     */
    void attach(AudioMixerListenerIfc* observer) final {
        Subject<AudioMixerListenerIfc>::attach(observer);
    }

    /**
     * @see SubjectIfc::detach
     */
    void detach(AudioMixerListenerIfc* observer) final {
        Subject<AudioMixerListenerIfc>::detach(observer);
    }

    /**
     * @see AudioMixerIfc::setOutputVolume
     */
    bool setOutputVolume(uint8_t volumePercent) final;

    /**
     * @see AudioMixerIfc::outputVolume
     */
    uint8_t outputVolume() const final;

private:

    struct MixerHandleDeleter final {
        void operator()(snd_mixer_t* handle) const;
    };

    struct MixerSettingDeleter final {
        void operator()(snd_mixer_selem_id_t* setting) const;
    };

    bool isInitializedLocked() const;
    snd_mixer_elem_t* findMixerElementLocked() const;
    void volumeWatchLoop();

    bool readVolumeLocked(uint8_t& volumePercent) const;
    bool writeVolumeLocked(uint8_t requestedPercent, uint8_t& actualPercent);

    mutable std::mutex m_mutex {};
    std::unique_ptr<snd_mixer_t, MixerHandleDeleter> m_mixerHandle {nullptr};
    std::unique_ptr<snd_mixer_selem_id_t, MixerSettingDeleter> m_mixerSetting {nullptr};
    mutable std::atomic_uint8_t m_cachedVolume {100};
    std::atomic_bool m_stopWatcher {false};
    std::thread m_volumeWatcher {};
};

#endif // SRC_PLATFORM_OS_INTERNAL_QLOCKY_AUDIO_OUTPUT_MIXER_H
