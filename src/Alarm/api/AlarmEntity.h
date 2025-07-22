#ifndef ALARM_ALARM_ENTITY_H
#define ALARM_ALARM_ENTITY_H

#include <cstdint>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

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
    AlarmId id;          // Unique identifier for the alarm
    std::string name;    // Name of the alarm
    bool isActive;       // Indicates if the alarm is currently active
    uint32_t dueTimeUtc; // Due time since 00:00 in UTC (seconds since start of day)
    bool repeated;       // Indicates if the alarm is repeated

    uint32_t snoozeTime {1U};    // Snooze time in minutes
    uint8_t maxSnoozeCount {3U}; // Maximum number of snoozes allowed
    uint8_t snoozeCount {0U};    // Current snooze count. Only temporary, not stored in the database.

    // TODO add other attributes: Snooze time, volume, light, sound, recurrent date, etc
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AlarmEntity, id, name, isActive, dueTimeUtc, repeated, maxSnoozeCount, snoozeTime)
};

#endif