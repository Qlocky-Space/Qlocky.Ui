#ifndef ALARM_REPOSITORY_H
#define ALARM_REPOSITORY_H

#include "AlarmRepositoryIfc.h"
#include "Mediator.h"
#include "PreferencesServiceIfc.h"

/**
 * @see AlarmRepositoryIfc
 *
 * This repository manages alarms and persists them using the PreferencesServiceIfc.
 * It provides methods to add, remove, and update alarms, and notifies subscribers of changes
 * through the Mediator.
 */
class AlarmRepository : public AlarmRepositoryIfc {
public:

    AlarmRepository(Mediator& mediator, PreferencesServiceIfc& persistency);

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
     * @see AlarmRepositoryIfc::alarms
     */
    std::vector<AlarmEntity> alarms() final {
        return m_alarms;
    }

private:

    Mediator& m_mediator;
    PreferencesServiceIfc& m_persistency;
    std::vector<AlarmEntity> m_alarms;
};

#endif