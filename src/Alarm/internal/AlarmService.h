#ifndef ALARM_SERVICE_H
#define ALARM_SERVICE_H

#include <api/Mediator.h>
#include <atomic>
#include <thread>
#include <TimeProviderIfc.h>

#include "AlarmServiceIfc.h"

/**
 * The alarm service provides the current time and checks if any alarm
 * condition is true. It sends all outputs with mediator events.
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

    Mediator& m_mediator;
    TimeProviderIfc const& m_timeProvider;

    std::atomic<bool> m_timerRunning;
    std::thread m_timerThread;
};

#endif