#include "AlarmPreferencesRepository.h"

std::string const AlarmPreferencesRepository::ALARM_PREFERENCES_NAMESPACE {"AlarmPreferences"};

AlarmPreferencesRepository::AlarmPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
}

void AlarmPreferencesRepository::initialize() {
    // Nothing to do
}

std::string AlarmPreferencesRepository::getTimeFormat() {
    // TODO log on error
    std::string const hFormat {getContext().getString(Preferences::PROP_24H_FORMAT).value()};

    std::string format {};
    format.append(hFormat);
    format.append(":");
    format.append("mm");

    return format;
}

std::string AlarmPreferencesRepository::getTimeZone() {
    auto& ctx = getContext();
    // TODO log on error
    std::string const prefTimeZone {getContext().getString(Preferences::PROP_TIMEZONE).value()};

    return prefTimeZone;
}
