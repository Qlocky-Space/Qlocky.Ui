#ifndef ALARM_SERVICE_H
#define ALARM_SERVICE_H

#include <api/Mediator.h>
#include <atomic>
#include <memory>
#include <thread>
#include <TimeProviderIfc.h>

#include "AlarmServiceIfc.h"

/**
 * The alarm service provides the current time and checks if any alarm
 * condition is true.
 *
 * It does not hold the alarm model list, but acts with the model and sends events to mediator.
 */
class AlarmService : public AlarmServiceIfc {
public:

    /**
     * Constructor for AlarmService.
     * @note use shared pointer to ensure lifetime is managed correctly.
     * @param mediator The mediator to communicate with other components.
     * @param timeProvider The time provider to get the current timestamp.
     */
    AlarmService(Mediator& mediator, std::shared_ptr<TimeProviderIfc> timeProvider);

    virtual ~AlarmService();

    /**
     * @see AlarmServiceIfc::initialize
     */
    void initialize() final;

private:

    void processTime();
    void updateTimestamp();
    void checkAlarmConditions();

    Mediator& m_mediator;
    std::shared_ptr<TimeProviderIfc> m_timeProvider;
    DateTime m_currentTimestamp;

    std::atomic<bool> m_timerRunning;
    std::thread m_timerThread;
};

#endif