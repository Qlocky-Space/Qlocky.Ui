#include "AlarmOverlaySelector.h"

AlarmOverlaySelector::AlarmOverlaySelector(Mediator& mediator, InteractiveNavigatorIfc& navigator) :
    m_navigator {navigator} {
    mediator.subscribe<AlarmActivatedEvent>(this, &AlarmOverlaySelector::onAlarmActivated);
}

void AlarmOverlaySelector::initialize() {
    // Nothing to do
}

void AlarmOverlaySelector::onAlarmActivated(AlarmActivatedEvent const& event) {
    if (isDeviceInSleepMode()) {
        showLockscreenOverlay(event);
    }
    else {
        showDialogOverlay(event);
    }
}

bool AlarmOverlaySelector::isDeviceInSleepMode() const {
    // TODO
    return false;
}

void AlarmOverlaySelector::showLockscreenOverlay(AlarmActivatedEvent const& event) {
    // TODO: Implement the logic to show the lockscreen overlay
}

void AlarmOverlaySelector::showDialogOverlay(AlarmActivatedEvent const& event) {
    UriQuery uri("qlocky://alarmActiveDialog");
    uri.addParam("alarmId", event.alarm.id);

    m_navigator.navigateTo(uri);
}
