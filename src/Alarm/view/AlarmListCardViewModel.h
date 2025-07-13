#ifndef ALARM_LIST_CARD_VIEW_MODEL_H
#define ALARM_LIST_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QQmlListProperty>

#include "AlarmListItemModel.h"

/**
 * View model for the alarm list card.
 */
class AlarmListCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<AlarmListItemModel> alarmList READ alarmList NOTIFY alarmListChanged)

public:

    AlarmListCardViewModel(Mediator& mediator);

    /**
     * Gets a list of alarm list items
     */
    QQmlListProperty<AlarmListItemModel> alarmList();

signals:
    void alarmListChanged();

private:

    QList<AlarmListItemModel*> m_alarms;

    // Static helper methods required by QQmlListProperty
    static void appendAlarm(QQmlListProperty<AlarmListItemModel>* list, AlarmListItemModel* alarm);
    static qsizetype alarmCount(QQmlListProperty<AlarmListItemModel>* list);
    static AlarmListItemModel* alarmAt(QQmlListProperty<AlarmListItemModel>* list, qsizetype index);
    static void clearAlarms(QQmlListProperty<AlarmListItemModel>* list);
};

#endif