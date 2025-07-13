#include "AlarmListCardViewModel.h"

AlarmListCardViewModel::AlarmListCardViewModel(Mediator& mediator) {
    auto* pAlarm = new AlarmListItemModel();
    pAlarm->setLabel("Label 1");
    pAlarm->setTime(QDateTime::currentDateTime());
    pAlarm->setActive(true);

    m_alarms.append(pAlarm);

    auto* pAlarm1 = new AlarmListItemModel();
    pAlarm1->setLabel("Label 2");
    pAlarm1->setTime(QDateTime::currentDateTime().addDays(5));
    pAlarm1->setActive(false);

    m_alarms.append(pAlarm1);
}

QQmlListProperty<AlarmListItemModel> AlarmListCardViewModel::alarmList() {
    return QQmlListProperty<AlarmListItemModel>(this, &m_alarms,
        &AlarmListCardViewModel::appendAlarm,
        &AlarmListCardViewModel::alarmCount,
        &AlarmListCardViewModel::alarmAt,
        &AlarmListCardViewModel::clearAlarms);
}

void AlarmListCardViewModel::appendAlarm(QQmlListProperty<AlarmListItemModel>* list, AlarmListItemModel* alarm) {
    auto* alarms = static_cast<QList<AlarmListItemModel*>*>(list->data);
    if (alarm) {
        alarms->append(alarm);
    }
}

qsizetype AlarmListCardViewModel::alarmCount(QQmlListProperty<AlarmListItemModel>* list) {
    auto* alarms = static_cast<QList<AlarmListItemModel*>*>(list->data);
    return alarms->size();
}

AlarmListItemModel* AlarmListCardViewModel::alarmAt(QQmlListProperty<AlarmListItemModel>* list, qsizetype index) {
    auto* alarms = static_cast<QList<AlarmListItemModel*>*>(list->data);
    return alarms->at(index);
}

void AlarmListCardViewModel::clearAlarms(QQmlListProperty<AlarmListItemModel>* list) {
    auto* alarms = static_cast<QList<AlarmListItemModel*>*>(list->data);
    alarms->clear();
}
