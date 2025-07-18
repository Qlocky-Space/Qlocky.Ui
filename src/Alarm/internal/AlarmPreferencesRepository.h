#ifndef ALARM_SETTING_REPOSITORY_H
#define ALARM_SETTING_REPOSITORY_H

#include "AlarmPreferencesRepositoryIfc.h"
#include "Mediator.h"
#include "PersistenceServiceIfc.h"

/**
 * @see AlarmPreferencesRepositoryIfc
 */
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

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
};

#endif