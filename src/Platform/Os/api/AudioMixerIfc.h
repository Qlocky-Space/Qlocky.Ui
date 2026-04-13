#ifndef SRC_PLATFORM_OS_API_AUDIO_MIXER_IFC_H
#define SRC_PLATFORM_OS_API_AUDIO_MIXER_IFC_H

#include <cstdint>

#include "AudioMixerListenerIfc.h"
#include "SubjectIfc.h"

/**
 * OS abstraction for controlling output volume.
 */
class AudioMixerIfc : public SubjectIfc<AudioMixerListenerIfc> {
public:

    virtual ~AudioMixerIfc() = default;

    /**
     * Set output volume percentage.
     * @param volumePercent Requested volume in range 0..100.
     * @return True if volume was applied successfully.
     */
    virtual bool setOutputVolume(uint8_t volumePercent) = 0;

    /**
     * Read current output volume percentage.
     * @return Actual volume in range 0..100.
     */
    virtual uint8_t outputVolume() const = 0;
};

#endif // SRC_PLATFORM_OS_API_AUDIO_MIXER_IFC_H
