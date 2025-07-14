#ifndef ALARM_REPOSITORY_IFC_H
#define ALARM_REPOSITORY_IFC_H

#include <vector>

#include "AlarmEntity.h"

/**
 * Represents an interface for an alarm repository.
 * This interface defines the basic operations for managing alarms.
 *
 * The implementation of this interface should handle the storage and retrieval of alarms.
 */
class AlarmRepositoryIfc {
public:

    virtual ~AlarmRepositoryIfc() = default;

    /**
     * Initializes the repository.
     * This method should be called to set up any necessary state or data structures.
     */
    virtual void initialize() = 0;

    /**
     * Adds a new alarm to the repository.
     * @param alarm The alarm entity to add.
     */
    virtual void addAlarm(AlarmEntity const& alarm) = 0;

    /**
     * Removes an alarm by its unique identifier.
     * @param id The unique identifier of the alarm.
     */
    virtual void removeAlarm(AlarmId const id) = 0;

    /**
     * Sets the state of an alarm (active/inactive).
     * @param id The unique identifier of the alarm.
     * @param isActive The new state of the alarm.
     */
    virtual void setAlarmState(AlarmId const id, bool isActive) = 0;

    /**
     * Retrieves all alarms.
     * @return Vector of all alarms.
     */
    virtual std::vector<AlarmEntity> alarms() = 0;
};

#endif