#ifndef ALARM_LIST_CARD_VIEW_MODEL_H
#define ALARM_LIST_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QQmlListProperty>

#include "AlarmListModel.h"

/**
 * View model for the alarm list card.
 *
 * Manages a list of individual alarm view models and provides methods
 * to activate or deactivate alarms. Designed for use in QML contexts.
 */
class AlarmListCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(AlarmListModel* alarms READ alarmList CONSTANT)

public:

    AlarmListCardViewModel(Mediator& mediator);

    /**
     * Gets a list of alarm list items
     */
    AlarmListModel* alarmList();

    /**
     * Activates the alarm with the specified ID.
     * @param alarmId The unique identifier of the alarm to activate.
     */
    Q_INVOKABLE void activateAlarm(int alarmId);

    /**
     * Deactivates the alarm with the specified ID.
     * @param alarmId The unique identifier of the alarm to deactivate.
     */
    Q_INVOKABLE void deactivateAlarm(int alarmId);

signals:
    void alarmListChanged();

private:

    AlarmListModel m_alarms;
};

#endif