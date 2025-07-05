#ifndef ALARM_PREFERENCES_DEFAULT_H
#define ALARM_PREFERENCES_DEFAULT_H

#include <string>

/**
 * List of alarm preferences defaults. Used when no other configuration is found
 */
struct AlarmPreferencesDefault final {
public:

    static std::string const DEFAULT_TIMEZONE;
    static std::string const DEFAULT_24H_FORMAT;
};

#endif