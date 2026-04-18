#ifndef SRC_DEVICE_INTERNAL_DISPLAY_SERVICE_H
#define SRC_DEVICE_INTERNAL_DISPLAY_SERVICE_H

#include <cstdint>

#include "DisplayControlIfc.h"
#include "DisplayServiceIfc.h"
#include "Mediator.h"
#include "SystemPreferencesRepositoryIfc.h"

class ApplicationStartedEvent;

/**
 * Default display service that applies persisted brightness and publishes brightness events.
 */
class DisplayService final : public DisplayServiceIfc {
public:

    DisplayService(Mediator& mediator, DisplayControlIfc& displayControl, SystemPreferencesRepositoryIfc& systemPreferences);

    /**
     * @see DisplayServiceIfc::~DisplayService
     */
    ~DisplayService() final;

    /**
     * @see DisplayServiceIfc::initialize
     */
    void initialize() final;

    /**
     * @see DisplayServiceIfc::setBrightnessPercent
     */
    void setBrightnessPercent(uint8_t brightnessPercent) final;

private:

    void onApplicationStarted(ApplicationStartedEvent const&);

    Mediator& m_mediator;
    DisplayControlIfc& m_displayControl;
    SystemPreferencesRepositoryIfc& m_systemPreferences;
};

#endif // SRC_DEVICE_INTERNAL_DISPLAY_SERVICE_H