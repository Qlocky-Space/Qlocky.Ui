#ifndef SRC_DEVICE_API_DISPLAY_SERVICE_IFC_H
#define SRC_DEVICE_API_DISPLAY_SERVICE_IFC_H

#include <cstdint>

/**
 * Service for display brightness business logic.
 */
class DisplayServiceIfc {
public:

    virtual ~DisplayServiceIfc() = default;

    /**
     * Initialize service subscriptions and state publication.
     */
    virtual void initialize() = 0;

    /**
     * Set brightness in range 0..100.
     */
    virtual void setBrightnessPercent(uint8_t brightnessPercent) = 0;
};

#endif // SRC_DEVICE_API_DISPLAY_SERVICE_IFC_H