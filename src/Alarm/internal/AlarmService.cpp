#include "AlarmService.h"

#include "TimeChangedEvent.h"

AlarmService::AlarmService(Mediator& mediator, TimeProviderIfc const& timeProvider) :
    m_mediator {mediator},
    m_timeProvider {timeProvider},
    m_timerRunning {true},
    m_timerThread {&AlarmService::processTime, this} {
}

AlarmService::~AlarmService() {
    m_timerRunning = false;

    if (m_timerThread.joinable()) {
        m_timerThread.join();
    }
}

void AlarmService::initialize() {
    // TODO
}

void AlarmService::processTime() {
    while (m_timerRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        updateTimestamp();
    }
}

void AlarmService::updateTimestamp() {
    DateTime const currentTimestamp {m_timeProvider.getCurrentTimestamp()};
    m_mediator.notify(TimeChangedEvent {currentTimestamp});
}
