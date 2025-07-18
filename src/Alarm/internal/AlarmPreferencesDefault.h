#ifndef ALARM_INTERNAL_ALARMPREFERENCESDEFAULT_H
#define ALARM_INTERNAL_ALARMPREFERENCESDEFAULT_H

#include <string>

#include "PersistenceItem.h"

/**
 * List of alarm preferences defaults.
 * Used when no other configuration is found.
 */
struct AlarmPreferencesDefault final {
public:

    /**
     * Namespace for alarm preferences.
     * @return The namespace used for storing alarm preferences.
     */
    static std::string const ALARM_PREFERENCES_NAMESPACE;

    /**
     * Default time zone string.
     * @return The default time zone used for alarms.
     */
    static constexpr PersistenceItem PROP_TIMEZONE {"TimeZone", "Europe/Zurich"};

    /**
     * Default 24-hour time format string.
     * @return The default time format used for displaying time.
     */
    static constexpr PersistenceItem PROP_24H_FORMAT {"24HFormat", "HH"};
};
#endif