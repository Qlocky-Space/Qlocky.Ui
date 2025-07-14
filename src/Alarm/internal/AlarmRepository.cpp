#include "AlarmRepository.h"

#include <algorithm>
#include <vector>

#include "events/AlarmAddedEvent.h"
#include "events/AlarmRemovedEvent.h"
#include "events/AlarmUpdatedEvent.h"

AlarmRepository::AlarmRepository(Mediator& mediator, PreferencesServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
}

void AlarmRepository::initialize() {
    m_alarms.clear();

    // TOOD just demo code, load from persistency
    AlarmEntity alarm1;
    alarm1.id = 0;
    alarm1.name = "Alarm 1";
    alarm1.isActive = true;
    alarm1.dueTime = 1752502140;
    addAlarm(alarm1);

    AlarmEntity alarm2;
    alarm2.id = 1;
    alarm2.name = "Alarm 2";
    alarm2.isActive = false;
    alarm2.dueTime = 1752508140;
    addAlarm(alarm2);
}

void AlarmRepository::addAlarm(AlarmEntity const& alarm) {
    auto it {std::find_if(m_alarms.begin(), m_alarms.end(),
        [&alarm](AlarmEntity const& a) { return a.id == alarm.id; })};

    if (it != m_alarms.end()) {
        *it = alarm;
        m_mediator.notify(AlarmUpdatedEvent {alarm});
    }
    else {
        m_alarms.push_back(alarm);
        m_mediator.notify(AlarmAddedEvent {alarm});
    }
}

void AlarmRepository::removeAlarm(AlarmId const id) {
    m_alarms.erase(
        std::remove_if(m_alarms.begin(), m_alarms.end(),
            [id](AlarmEntity const& a) {
                return a.id == id;
            }),
        m_alarms.end());
    m_mediator.notify(AlarmRemovedEvent {id});
}

void AlarmRepository::setAlarmState(AlarmId const id, bool isActive) {
    auto it {std::find_if(m_alarms.begin(), m_alarms.end(),
        [id](AlarmEntity const& a) { return a.id == id; })};

    if (it != m_alarms.end()) {
        it->isActive = isActive;
        m_mediator.notify(AlarmUpdatedEvent {*it});
    }
}
