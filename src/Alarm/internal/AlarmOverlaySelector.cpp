#include "AlarmOverlaySelector.h"

AlarmOverlaySelector::AlarmOverlaySelector(Mediator& mediator, InteractiveNavigatorIfc& navigator, RadioServiceIfc& radioService, RadioPlayerIfc& radioPlayer) :
    m_navigator {navigator},
    m_radioService {radioService},
    m_radioPlayer {radioPlayer},
    m_activeAlarmId {} {
    mediator.subscribe<AlarmActivatedEvent>(this, &AlarmOverlaySelector::onAlarmActivated);
    mediator.subscribe<AlarmUpdatedEvent>(this, &AlarmOverlaySelector::onAlarmUpdated);
}

void AlarmOverlaySelector::initialize() {
    // Nothing to do
}

void AlarmOverlaySelector::onAlarmActivated(AlarmActivatedEvent const& event) {
    m_activeAlarmId = event.alarm.id;
    startRadioForAlarm(event.alarm);

    if (isDeviceInSleepMode()) {
        showLockscreenOverlay(event);
    }
    else {
        showDialogOverlay(event);
    }
}

void AlarmOverlaySelector::onAlarmUpdated(AlarmUpdatedEvent const& event) {
    if (!m_activeAlarmId.has_value() || m_activeAlarmId.value() != event.alarm.id) {
        return;
    }

    if (event.alarm.snoozeCount > 0) {
        return;
    }

    m_radioPlayer.stop();
    m_activeAlarmId.reset();
}

bool AlarmOverlaySelector::isDeviceInSleepMode() const {
    // TODO
    return false;
}

void AlarmOverlaySelector::startRadioForAlarm(AlarmEntity const& alarm) {
    if (alarm.musicSourceId.empty()) {
        return;
    }

    AlarmId const alarmId {alarm.id};
    m_radioService.resolveRadioById(alarm.musicSourceId, [this, alarmId](std::optional<RadioEntity> const& radio) {
        if (!radio.has_value()) {
            return;
        }

        if (!m_activeAlarmId.has_value() || m_activeAlarmId.value() != alarmId) {
            return;
        }

        m_radioService.selectRadio(*radio);
        m_radioPlayer.play(*radio);
    });
}

void AlarmOverlaySelector::showLockscreenOverlay(AlarmActivatedEvent const& event) {
    // TODO: Implement the logic to show the lockscreen overlay
}

void AlarmOverlaySelector::showDialogOverlay(AlarmActivatedEvent const& event) {
    UriQuery uri("qlocky://alarmActiveDialog");
    uri.addParam("alarmId", event.alarm.id);

    m_navigator.navigateTo(uri);
}
