#include "SystemPreferencesRepository.h"

#include <ng-log/logging.h>

std::string const SystemPreferencesRepository::SYSTEM_PREFERENCES_NAMESPACE {"SystemPreferences"};

SystemPreferencesRepository::SystemPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
}

void SystemPreferencesRepository::initialize() {
    // Nothing to do
}

std::string SystemPreferencesRepository::getTimeFormat() {
    auto result {getContext().getBool(Preferences::PROP_24H_FORMAT_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get time format: " << result.error();
    }

    bool is24HourFormat {result.valueOr(true)};
    return is24HourFormat ? "HH:mm" : "hh:mm AP";
}

std::string SystemPreferencesRepository::getTimeZone() {
    auto result {getContext().getString(Preferences::PROP_TIMEZONE_KEY)};
    if (result.isError()) {
        DLOG_FIRST_N(WARNING, 1) << "Failed to get time zone: " << result.error();
    }
    // Default to UTC+02:00 if not set
    std::string const prefTimeZone {result.valueOr("UTC+02:00")};

    return prefTimeZone;
}
