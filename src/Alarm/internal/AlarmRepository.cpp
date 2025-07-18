#include "AlarmRepository.h"

#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

#include "events/AlarmAddedEvent.h"
#include "events/AlarmRemovedEvent.h"
#include "events/AlarmUpdatedEvent.h"

std::string const AlarmRepository::ALARM_NAMESPACE {"Alarms"};

AlarmRepository::AlarmRepository(Mediator& mediator, PersistenceServiceIfc& persistency) :
    m_mediator {mediator},
    m_persistency {persistency} {
}

void AlarmRepository::initialize() {
    m_alarms.clear();

    auto result {getContext().getList(Preferences::PROP_ITEMS_KEY)};
    if (result.isError()) {
        // TODO log error
        std::cerr << "Failed to get alarms: " << result.error() << std::endl;
        return;
    }

    for (auto& [key, obj] : result.value()) {
        auto json = nlohmann::json::parse(obj);
        auto alarm = json.get<AlarmEntity>();
        m_alarms.push_back(alarm);
        m_mediator.notify(AlarmAddedEvent {alarm});
    }
}

void AlarmRepository::addAlarm(AlarmEntity const& alarm) {
    auto it {std::find_if(m_alarms.begin(), m_alarms.end(),
        [&alarm](AlarmEntity const& a) { return a.id == alarm.id; })};

    ResultVoid const result {updateObject(alarm)};
    if (result.isError()) {
        // TODO log error
        std::cerr << "Failed to update alarm: " << result.error() << std::endl;
        return;
    }

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

    ResultVoid const result {removeObject(id)};
    if (result.isError()) {
        // TODO log error
        std::cerr << "Failed to remove alarm: " << result.error() << std::endl;
        return;
    }

    m_mediator.notify(AlarmRemovedEvent {id});
}

void AlarmRepository::setAlarmState(AlarmId const id, bool isActive) {
    auto it {std::find_if(m_alarms.begin(), m_alarms.end(),
        [id](AlarmEntity const& a) { return a.id == id; })};

    if (it == m_alarms.end()) {
        return;
    }

    // update the state
    it->isActive = isActive;

    ResultVoid const result {updateObject(*it)};
    if (result.isError()) {
        // TODO log error
        std::cerr << "Failed to update alarm: " << result.error() << std::endl;
        return;
    }

    m_mediator.notify(AlarmUpdatedEvent {*it});
}

ResultVoid AlarmRepository::updateObject(AlarmEntity const& alarm) {
    return getContext().setListItem(Preferences::PROP_ITEMS_KEY, alarm.id, nlohmann::json(alarm).dump());
}

ResultVoid AlarmRepository::removeObject(AlarmId const& alarmId) {
    return getContext().removeListItem(Preferences::PROP_ITEMS_KEY, alarmId);
}
