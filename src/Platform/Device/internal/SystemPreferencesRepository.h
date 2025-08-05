#ifndef SYSTEM_PREFERENCES_REPOSITORY_H
#define SYSTEM_PREFERENCES_REPOSITORY_H

#include "Mediator.h"
#include "PersistenceServiceIfc.h"
#include "SystemPreferencesRepositoryIfc.h"

/**
 * @see SystemPreferencesRepositoryIfc
 */
class SystemPreferencesRepository : public SystemPreferencesRepositoryIfc {
public:

    SystemPreferencesRepository(Mediator& mediator, PersistenceServiceIfc& persistency);

    /**
     * @see SystemPreferencesRepositoryIfc::initialize
     */
    void initialize() final;

    /**
     * @see SystemPreferencesRepositoryIfc::getTimeFormat
     */
    std::string getTimeFormat() final;

    /**
     * @see SystemPreferencesRepositoryIfc::getTimeZone
     */
    std::string getTimeZone() final;

private:

    static std::string const SYSTEM_PREFERENCES_NAMESPACE;

    struct Preferences final {
        inline static std::string const PROP_TIMEZONE_KEY {"TimeZone"};
        inline static std::string const PROP_24H_FORMAT_KEY {"24HFormat"};
    };

    KeyValueDatabaseIfc& getContext() {
        return m_persistency.getContext(SYSTEM_PREFERENCES_NAMESPACE);
    }

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
};

#endif