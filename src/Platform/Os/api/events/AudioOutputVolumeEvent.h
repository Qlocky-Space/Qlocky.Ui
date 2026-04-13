#ifndef SRC_PLATFORM_OS_API_EVENTS_AUDIO_OUTPUT_VOLUME_EVENT_H
#define SRC_PLATFORM_OS_API_EVENTS_AUDIO_OUTPUT_VOLUME_EVENT_H

#include <cstdint>

#include "EventIfc.h"

/**
 * Event carrying the current audio output volume.
 */
class AudioOutputVolumeEvent final : public EventIfc {
public:

    AudioOutputVolumeEvent() = default;
    ~AudioOutputVolumeEvent() final = default;

    /**
     * @param volumePercent Actual volume in range 0..100.
     */
    explicit AudioOutputVolumeEvent(uint8_t volumePercent) :
        m_volumePercent {volumePercent} {
    }

    /**
     * @return Current volume in range 0..100.
     */
    uint8_t volumePercent() const {
        return m_volumePercent;
    }

private:

    uint8_t m_volumePercent {0};
};

#endif // SRC_PLATFORM_OS_API_EVENTS_AUDIO_OUTPUT_VOLUME_EVENT_H
