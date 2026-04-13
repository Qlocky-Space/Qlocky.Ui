#ifndef SRC_PLATFORM_OS_API_AUDIO_MIXER_LISTENER_IFC_H
#define SRC_PLATFORM_OS_API_AUDIO_MIXER_LISTENER_IFC_H

#include <cstdint>

/**
 * Listener for OS audio mixer state changes.
 */
class AudioMixerListenerIfc {
public:

    virtual ~AudioMixerListenerIfc() = default;

    /**
     * Called when the actual output volume changes.
     * @param volumePercent Actual volume in range 0..100.
     */
    virtual void onVolumeChanged(uint8_t volumePercent) = 0;
};

#endif // SRC_PLATFORM_OS_API_AUDIO_MIXER_LISTENER_IFC_H
