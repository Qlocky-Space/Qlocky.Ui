#ifndef SRC_PLATFORM_OS_INTERNAL_MOCK_DISPLAY_CONTROL_STUB_H
#define SRC_PLATFORM_OS_INTERNAL_MOCK_DISPLAY_CONTROL_STUB_H

#include "DisplayControlIfc.h"

/**
 * Mock display control implementation for testing and non-embedded platforms.
 */
class DisplayControlStub final : public DisplayControlIfc {
public:

    /**
     * @see DisplayControlIfc::turnOn
     */
    void turnOn() final;

    /**
     * @see DisplayControlIfc::turnOff
     */
    void turnOff() final;

    /**
     * @see DisplayControlIfc::dim
     */
    void dim(uint8_t level) final;
};

#endif // SRC_PLATFORM_OS_INTERNAL_MOCK_DISPLAY_CONTROL_STUB_H
