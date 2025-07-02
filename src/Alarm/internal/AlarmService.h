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

    AlarmService(Mediator& mediator, TimeProviderIfc const& timeProvider);

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
    TimeProviderIfc const& m_timeProvider;
    DateTime m_currentTimestamp;

    std::atomic<bool> m_timerRunning;
    std::thread m_timerThread;
};

#endif