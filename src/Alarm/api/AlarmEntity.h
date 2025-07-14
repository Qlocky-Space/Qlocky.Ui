#ifndef ALARM_ALARM_ENTITY_H
#define ALARM_ALARM_ENTITY_H

#include <optional>
#include <string>

/**
 * Represents unique identifier for an alarm.
 */
using AlarmId = int;

/**
 * Represents an alarm entity.
 *
 * This struct encapsulates the properties of an alarm.
 */
struct AlarmEntity {
    AlarmId id;       // Unique identifier for the alarm
    std::string name; // Name of the alarm
    bool isActive;    // Indicates if the alarm is currently active
    int64_t dueTime;  // Schedule for the alarm, including recurrence rules

    // TODO add other attributes: Snooze time, volume, light, sound, recurrent date, etc
};

#endif