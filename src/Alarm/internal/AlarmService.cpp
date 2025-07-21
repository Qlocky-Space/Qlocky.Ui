#include "AlarmService.h"

#include <iostream>
#include <QDateTime>
#include <QTimeZone>

#include "events/AlarmActivatedEvent.h"
#include "events/ApplicationClosedEvent.h"
#include "TimeChangedEvent.h"

AlarmService::AlarmService(Mediator& mediator, TimeProviderIfc& timeProvider, AlarmRepositoryIfc& alarmRepository) :
    m_mediator {mediator},
    m_timeProvider {timeProvider},
    m_alarmRepository {alarmRepository},
    m_currentTimestamp {0ULL},
    m_timerRunning {true},
    m_timerThread {} {
    mediator.subscribe<ApplicationClosedEvent>([this](ApplicationClosedEvent const&) { stop(); });
}

void AlarmService::initialize() {
    // create and start timerThread
    m_timerRunning = true;
    m_timerThread = std::thread(&AlarmService::processTime, this);
}

void AlarmService::stop() {
    m_timerRunning = false;

    if (m_timerThread.joinable()) {
        m_timerThread.join();
    }
}

void AlarmService::processTime() {
    while (m_timerRunning) {
        updateTimestamp();
        checkAlarmConditions();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void AlarmService::updateTimestamp() {
    m_currentTimestamp = m_timeProvider.getCurrentTimestamp();
    m_mediator.notify(TimeChangedEvent {m_currentTimestamp});
}

void AlarmService::checkAlarmConditions() {
    for (AlarmEntity const& alarm : m_alarmRepository.alarms()) {
        // Check if the alarm should be activated based on the current timestamp
        if (shouldActivateAlarm(alarm, m_currentTimestamp)) {
            m_mediator.notify(AlarmActivatedEvent {alarm});
        }
    }
}

bool AlarmService::shouldActivateAlarm(AlarmEntity const& alarm, DateTime const currentTimestamp) {
    if (!alarm.isActive) {
        return false;
    }

    // Convert the current timestamp to relative UTC time. Start of day is 00:00 UTC.
    // This is the number of seconds since the start of the day in UTC.
    uint32_t const currentTimeUtc {QDateTime::fromSecsSinceEpoch(currentTimestamp, QTimeZone::utc()).time().msecsSinceStartOfDay() / 1000U};

    // TODO check also recurrent dates, e.g. every day at 8:00
    // For now, we only check if the hours and minutes match

    if (alarm.dueTimeUtc == currentTimeUtc) {
        return true;
    }

    return false;
}
