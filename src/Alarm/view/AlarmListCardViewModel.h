#ifndef ALARM_LIST_CARD_VIEW_MODEL_H
#define ALARM_LIST_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QQmlListProperty>

#include "AlarmListModel.h"
#include "events/AlarmAddedEvent.h"
#include "events/AlarmRemovedEvent.h"
#include "events/AlarmUpdatedEvent.h"
#include "internal/AlarmRepositoryIfc.h"

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

    AlarmListCardViewModel(Mediator& mediator, AlarmRepositoryIfc& repository);

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

    void onAlarmAdded(AlarmAddedEvent const& event);
    void onAlarmRemoved(AlarmRemovedEvent const& event);
    void onAlarmUpdated(AlarmUpdatedEvent const& event);

    AlarmListModel m_alarms;
    AlarmRepositoryIfc& m_repository;
};

#endif