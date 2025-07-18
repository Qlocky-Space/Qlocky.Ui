#include <algorithm>
#include <vector>

#include "AlarmPreferencesDefault.h"
#include "AlarmPreferencesRepository.h"

AlarmPreferencesRepository::AlarmPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
}

void AlarmPreferencesRepository::initialize() {
    // Nothing to do
}

std::string AlarmPreferencesRepository::getTimeFormat() {
    auto& ctx {m_persistency.getContext(AlarmPreferencesDefault::ALARM_PREFERENCES_NAMESPACE)};
    std::string const hFormat {ctx.getString(AlarmPreferencesDefault::PROP_24H_FORMAT)};

    std::string format {};
    format.append(hFormat);
    format.append(":");
    format.append("mm");

    return format;
}

std::string AlarmPreferencesRepository::getTimeZone() {
    auto& ctx = m_persistency.getContext(AlarmPreferencesDefault::ALARM_PREFERENCES_NAMESPACE);
    std::string const prefTimeZone {ctx.getString(AlarmPreferencesDefault::PROP_TIMEZONE)};

    return prefTimeZone;
}
