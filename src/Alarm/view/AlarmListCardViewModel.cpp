#include "AlarmListCardViewModel.h"

AlarmListCardViewModel::AlarmListCardViewModel(Mediator& mediator) {
    // TODO replace demo code with mediator AlarmAddedEvent/AlarmRemovedEvent/AlarmUpdateEvent

    auto* pAlarm = new AlarmItemViewModel(0);
    pAlarm->setLabel("Label 1");
    pAlarm->setTime(QDateTime::currentDateTime());
    pAlarm->setActive(true);
    addAlarm(*pAlarm);

    auto* pAlarm1 = new AlarmItemViewModel(1);
    pAlarm1->setLabel("Label 2");
    pAlarm1->setTime(QDateTime::currentDateTime().addDays(5));
    pAlarm1->setActive(false);
    addAlarm(*pAlarm1);
}

QQmlListProperty<AlarmItemViewModel> AlarmListCardViewModel::alarmList() {
    return QQmlListProperty<AlarmItemViewModel>(this, &m_alarms,
        &AlarmListCardViewModel::appendAlarm,
        &AlarmListCardViewModel::alarmCount,
        &AlarmListCardViewModel::alarmAt,
        &AlarmListCardViewModel::clearAlarms);
}

void AlarmListCardViewModel::addAlarm(AlarmItemViewModel& alarm) {
    m_alarms.append(&alarm);
    connect(&alarm, &AlarmItemViewModel::changed, this, &AlarmListCardViewModel::onAlarmChanged);
    emit alarmListChanged();
}

void AlarmListCardViewModel::removeAlarm(AlarmItemViewModel& alarm) {
    if (m_alarms.removeOne(&alarm)) {
        emit alarmListChanged();
    }
}

void AlarmListCardViewModel::onAlarmChanged(AlarmItemViewModel const* alarm) {
    // TODO update AlarmRepositoryIfc
}

void AlarmListCardViewModel::appendAlarm(QQmlListProperty<AlarmItemViewModel>* list, AlarmItemViewModel* alarm) {
    auto* alarms = static_cast<QList<AlarmItemViewModel*>*>(list->data);
    if (alarm) {
        alarms->append(alarm);
    }
}

qsizetype AlarmListCardViewModel::alarmCount(QQmlListProperty<AlarmItemViewModel>* list) {
    auto* alarms = static_cast<QList<AlarmItemViewModel*>*>(list->data);
    return alarms->size();
}

AlarmItemViewModel* AlarmListCardViewModel::alarmAt(QQmlListProperty<AlarmItemViewModel>* list, qsizetype index) {
    auto* alarms = static_cast<QList<AlarmItemViewModel*>*>(list->data);
    return alarms->at(index);
}

void AlarmListCardViewModel::clearAlarms(QQmlListProperty<AlarmItemViewModel>* list) {
    auto* alarms = static_cast<QList<AlarmItemViewModel*>*>(list->data);
    alarms->clear();
}
