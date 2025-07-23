#ifndef DAY_OF_WEEK_H
#define DAY_OF_WEEK_H

#include <cstdint>

/**
 * Represents the days of the week using bit flags.
 * This allows for easy combination and manipulation of days.
 */
enum class DayOfWeek : uint8_t {
    None = 0,
    Monday = 1 << 0,
    Tuesday = 1 << 1,
    Wednesday = 1 << 2,
    Thursday = 1 << 3,
    Friday = 1 << 4,
    Saturday = 1 << 5,
    Sunday = 1 << 6
};

/**
 * Checks if a specific day is set in the given days of the week.
 * @param days The days of the week to check.
 * @param day The specific day to check.
 * @return True if the specific day is set in the days of the week, false otherwise
 */
inline bool isDayOfWeekSet(DayOfWeek days, DayOfWeek day) {
    return static_cast<uint8_t>(days) & static_cast<uint8_t>(day);
}

#endif