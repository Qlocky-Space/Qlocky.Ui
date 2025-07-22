#ifndef INTERNAL_ALARMOVERLAYSELECTOR_H
#define INTERNAL_ALARMOVERLAYSELECTOR_H

#include <cinttypes>
#include <Mediator.h>
#include <Navigation/InteractiveNavigatorIfc.h>

#include "events/AlarmActivatedEvent.h"

/**
 * Selects and displays the appropriate alarm overlay based on device state.
 * Shows the lockscreen overlay if the device is in sleep mode, otherwise opens a dialog.
 */
class AlarmOverlaySelector {

public:

    /**
     * Constructs an AlarmOverlaySelector.
     */
    explicit AlarmOverlaySelector(Mediator& mediator, InteractiveNavigatorIfc& navigator);

    /**
     * Initializes the selector
     */
    void initialize();

private:

    void onAlarmActivated(AlarmActivatedEvent const& event);
    bool isDeviceInSleepMode() const;
    void showLockscreenOverlay(AlarmActivatedEvent const& event);
    void showDialogOverlay(AlarmActivatedEvent const& event);

    InteractiveNavigatorIfc& m_navigator;
};

#endif //