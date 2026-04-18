#ifndef SRC_PLATFORM_OS_API_EVENTS_DISPLAY_BRIGHTNESS_CHANGED_EVENT_H
#define SRC_PLATFORM_OS_API_EVENTS_DISPLAY_BRIGHTNESS_CHANGED_EVENT_H

#include <cstdint>
#include <EventIfc.h>

/**
 * Published when the display brightness changes.
 */
class DisplayBrightnessChangedEvent final : public EventIfc {
public:

    DisplayBrightnessChangedEvent() = default;
    ~DisplayBrightnessChangedEvent() final = default;

    explicit DisplayBrightnessChangedEvent(uint8_t brightnessPercent) :
        m_brightnessPercent {brightnessPercent} {
    }

    uint8_t brightnessPercent() const {
        return m_brightnessPercent;
    }

private:

    uint8_t m_brightnessPercent {100};
};

#endif // SRC_PLATFORM_OS_API_EVENTS_DISPLAY_BRIGHTNESS_CHANGED_EVENT_H