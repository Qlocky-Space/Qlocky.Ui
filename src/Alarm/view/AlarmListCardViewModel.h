#ifndef ALARM_LIST_CARD_VIEW_MODEL_H
#define ALARM_LIST_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QQmlListProperty>

#include "AlarmItemViewModel.h"

/**
 * View model for the alarm list card.
 */
class AlarmListCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<AlarmItemViewModel> alarmList READ alarmList NOTIFY alarmListChanged)

public:

    AlarmListCardViewModel(Mediator& mediator);

    /**
     * Gets a list of alarm list items
     */
    QQmlListProperty<AlarmItemViewModel> alarmList();

signals:
    void alarmListChanged();

private:

    QList<AlarmItemViewModel*> m_alarms;

    void addAlarm(AlarmItemViewModel& alarm);
    void removeAlarm(AlarmItemViewModel& alarm);
    void onAlarmChanged(AlarmItemViewModel const* alarm);

    // Static helper methods required by QQmlListProperty
    static void appendAlarm(QQmlListProperty<AlarmItemViewModel>* list, AlarmItemViewModel* alarm);
    static qsizetype alarmCount(QQmlListProperty<AlarmItemViewModel>* list);
    static AlarmItemViewModel* alarmAt(QQmlListProperty<AlarmItemViewModel>* list, qsizetype index);
    static void clearAlarms(QQmlListProperty<AlarmItemViewModel>* list);
};

#endif