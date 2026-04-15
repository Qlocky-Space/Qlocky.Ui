#ifndef ALARM_ALARM_ENTITY_H
#define ALARM_ALARM_ENTITY_H

#include <cstdint>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

#include "DayOfWeek.h"

/**
 * Represents unique identifier for an alarm.
 */
using AlarmId = uint32_t;

/**
 * Represents an alarm entity.
 *
 * This struct encapsulates the properties of an alarm.
 */
struct AlarmEntity {
    AlarmId id;           // Unique identifier for the alarm
    std::string name;     // Name of the alarm
    bool isActive;        // Indicates if the alarm is currently active
    uint32_t dueTimeUtc;  // Due time since 00:00 in UTC (seconds since start of day)
    DayOfWeek daysOfWeek; // Days of the week when the alarm is active

    uint32_t snoozeTime;         // Snooze time in minutes
    uint8_t maxSnoozeCount;      // Maximum number of snoozes allowed
    std::string musicSourceId;   // Radio source identifier for the alarm music
    std::string musicSourceName; // Display name of the selected music source. Used to display name without music service lookup.

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AlarmEntity, id, name, isActive, dueTimeUtc, daysOfWeek, maxSnoozeCount, snoozeTime, musicSourceId, musicSourceName)

    uint8_t snoozeCount; // Current snooze count. Only temporary, not stored in the database.
};

#endif