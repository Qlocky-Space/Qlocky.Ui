#ifndef INTERNAL_ALARMOVERLAYSELECTOR_H
#define INTERNAL_ALARMOVERLAYSELECTOR_H

#include <ApplicationLifecycleIfc.h>
#include <cinttypes>
#include <Mediator.h>
#include <Navigation/InteractiveNavigatorIfc.h>
#include <optional>
#include <RadioPlayerIfc.h>
#include <RadioServiceIfc.h>
#include <Task.h>

#include "events/AlarmActivatedEvent.h"
#include "events/AlarmUpdatedEvent.h"

/**
 * Selects and displays the appropriate alarm overlay based on device state.
 * Shows the lockscreen overlay if the device is in sleep mode, otherwise opens a dialog.
 */
class AlarmOverlaySelector {

public:

    /**
     * Constructs an AlarmOverlaySelector.
     */
    explicit AlarmOverlaySelector(Mediator& mediator, InteractiveNavigatorIfc& navigator, RadioServiceIfc& radioService, RadioPlayerIfc& radioPlayer, ApplicationLifecycleIfc& lifecycle);

    /**
     * Initializes the selector
     */
    void initialize();

private:

    DetachedTask onAlarmActivated(AlarmActivatedEvent const& event);
    void onAlarmUpdated(AlarmUpdatedEvent const& event);
    bool isDeviceInSleepMode() const;
    Task<void> startRadioForAlarm(AlarmEntity const& alarm);
    void showLockscreenOverlay(AlarmActivatedEvent const& event);
    void showDialogOverlay(AlarmActivatedEvent const& event);

    InteractiveNavigatorIfc& m_navigator;
    RadioServiceIfc& m_radioService;
    RadioPlayerIfc& m_radioPlayer;
    ApplicationLifecycleIfc& m_lifecycle;
    std::optional<AlarmId> m_activeAlarmId;
};

#endif // INTERNAL_ALARMOVERLAYSELECTOR_H