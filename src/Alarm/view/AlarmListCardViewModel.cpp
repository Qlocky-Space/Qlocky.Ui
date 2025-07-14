#include "AlarmListCardViewModel.h"

AlarmListCardViewModel::AlarmListCardViewModel(Mediator& mediator) {
    // TODO replace demo code with mediator AlarmAddedEvent/AlarmRemovedEvent/AlarmUpdateEvent

    auto* pAlarm = new AlarmItemViewModel(0);
    pAlarm->setDisplayName("Label 1");
    pAlarm->setDueTime(QDateTime::currentDateTime());
    pAlarm->setState(true);
    m_alarms.addAlarm(pAlarm);

    auto* pAlarm1 = new AlarmItemViewModel(1);
    pAlarm1->setDisplayName("Label 2");
    pAlarm1->setDueTime(QDateTime::currentDateTime().addDays(5));
    pAlarm1->setState(false);
    m_alarms.addAlarm(pAlarm1);
}

AlarmListModel* AlarmListCardViewModel::alarmList() {
    return &m_alarms;
}

void AlarmListCardViewModel::activateAlarm(int alarmId) {
    // TODO AlarmRepositoryIfc::setAlarmState(alarmId, true)
}

void AlarmListCardViewModel::deactivateAlarm(int alarmId) {
    // TODO AlarmRepositoryIfc::setAlarmState(alarmId, false)
}
