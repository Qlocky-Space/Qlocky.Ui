#ifndef SRC_PLATFORM_OS_API_DISPLAY_CONTROL_IFC_H
#define SRC_PLATFORM_OS_API_DISPLAY_CONTROL_IFC_H

/**
 * Controls display power state and brightness. Touch screen remains functional even when display is off.
 */
class DisplayControlIfc {
public:

    virtual ~DisplayControlIfc() = default;

    /**
     * Turn display on.
     */
    virtual void turnOn() = 0;

    /**
     * Turn display off. Touch screen remains active.
     */
    virtual void turnOff() = 0;

    /**
     * Dim the display to the given level while keeping it logically on.
     *
     * @param level Dim level from 0 (no dimming, full brightness) to 100 (fully black, display still on).
     */
    virtual void dim(uint8_t level) = 0;
};

#endif // SRC_PLATFORM_OS_API_DISPLAY_CONTROL_IFC_H
