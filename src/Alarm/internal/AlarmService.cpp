#include "AlarmService.h"

#include "TimeChangedEvent.h"

AlarmService::AlarmService(Mediator& mediator, std::shared_ptr<TimeProviderIfc> timeProvider) :
    m_mediator {mediator},
    m_timeProvider {timeProvider},
    m_currentTimestamp {0ULL},
    m_timerRunning {true},
    m_timerThread {} {
}

AlarmService::~AlarmService() {
    m_timerRunning = false;

    if (m_timerThread.joinable()) {
        m_timerThread.join();
    }
}

void AlarmService::initialize() {
    // create and start timerThread
    m_timerRunning = true;
    m_timerThread = std::thread(&AlarmService::processTime, this);
}

void AlarmService::processTime() {
    while (m_timerRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        updateTimestamp();
        checkAlarmConditions();
    }
}

void AlarmService::updateTimestamp() {
    m_currentTimestamp = m_timeProvider->getCurrentTimestamp();
    m_mediator.notify(TimeChangedEvent {m_currentTimestamp});
}

void AlarmService::checkAlarmConditions() {
    // TODO Alarm Feature
    // check if any alarm conditions (get alarms from AlarmPersistency)
    // is true and notify mediator with AlarmActivatedEvent(alarm).
    //
    // Alarm can be snoozed/stopped with e.g. AlarmService::snooze(alarmId, 10min)
    // which sends an AlarmDeactivedEvent(alarm, Reason::Snooze)
}
