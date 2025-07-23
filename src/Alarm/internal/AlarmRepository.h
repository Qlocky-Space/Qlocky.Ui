#ifndef ALARM_REPOSITORY_H
#define ALARM_REPOSITORY_H

#include "AlarmRepositoryIfc.h"
#include "Mediator.h"
#include "PersistenceServiceIfc.h"

/**
 * @see AlarmRepositoryIfc
 *
 * This repository manages alarms and persists them using the PersistenceServiceIfc.
 * It provides methods to add, remove, and update alarms, and notifies subscribers of changes
 * through the Mediator.
 */
class AlarmRepository : public AlarmRepositoryIfc {
public:

    AlarmRepository(Mediator& mediator, PersistenceServiceIfc& persistency);

    /**
     * @see AlarmRepositoryIfc::initialize
     */
    void initialize() final;

    /**
     * @see AlarmRepositoryIfc::addAlarm
     */
    void addAlarm(AlarmEntity const& alarm) final;

    /**
     * @see AlarmRepositoryIfc::removeAlarm
     */
    void removeAlarm(AlarmId const id) final;

    /**
     * @see AlarmRepositoryIfc::setAlarmState
     */
    void setAlarmState(AlarmId const id, bool isActive) final;

    /**
     * @see AlarmRepositoryIfc::snooze
     */
    void snooze(AlarmId const alarmId) final;

    /**
     * @see AlarmRepositoryIfc::alarms
     */
    std::vector<AlarmEntity> alarms() final {
        return m_alarms;
    }

private:

    static std::string const ALARM_NAMESPACE;

    struct Preferences final {
        inline static std::string const PROP_ITEMS_KEY {"Items"};
    };

    KeyValueDatabaseIfc& getContext() {
        return m_persistency.getContext(ALARM_NAMESPACE);
    }

    ResultVoid updateObject(AlarmEntity const& alarm);
    ResultVoid removeObject(AlarmId const& alarmId);

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
    std::vector<AlarmEntity> m_alarms;
};

#endif