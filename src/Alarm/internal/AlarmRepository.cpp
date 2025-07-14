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

    auto* pAlarm = new AlarmEntity();
    pAlarm->id = 0;
    pAlarm->name = "Alarm 1";
    pAlarm->isActive = true;
    pAlarm->dueTime = 1752502140;
    addAlarm(*pAlarm);

    auto* pAlarm2 = new AlarmEntity();
    pAlarm2->id = 1;
    pAlarm2->name = "Alarm 2";
    pAlarm2->isActive = false;
    pAlarm2->dueTime = 1752508140;
    addAlarm(*pAlarm2);
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
