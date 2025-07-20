#ifndef ALARM_SETTING_REPOSITORY_H
#define ALARM_SETTING_REPOSITORY_H

#include "AlarmPreferencesRepositoryIfc.h"
#include "Mediator.h"
#include "PersistenceServiceIfc.h"

/**
 * @see AlarmPreferencesRepositoryIfc
 */
// TODO all system preferences should be moved to a common repository
class AlarmPreferencesRepository : public AlarmPreferencesRepositoryIfc {
public:

    AlarmPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency);

    /**
     * @see AlarmPreferencesRepositoryIfc::initialize
     */
    void initialize() final;

    /**
     * @see AlarmPreferencesRepositoryIfc::getTimeFormat
     */
    std::string getTimeFormat() final;

    /**
     * @see AlarmPreferencesRepositoryIfc::getTimeZone
     */
    std::string getTimeZone() final;

private:

    static std::string const ALARM_PREFERENCES_NAMESPACE;

    struct Preferences final {
        inline static std::string const PROP_TIMEZONE_KEY {"TimeZone"};
        inline static std::string const PROP_24H_FORMAT_KEY {"24HFormat"};
    };

    KeyValueDatabaseIfc& getContext() {
        return m_persistency.getContext(ALARM_PREFERENCES_NAMESPACE);
    }

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
};

#endif