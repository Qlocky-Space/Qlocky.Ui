#include "AlarmListCardViewModel.h"

#include "../internal/AlarmMapper.h"

AlarmListCardViewModel::AlarmListCardViewModel(Mediator& mediator, AlarmRepositoryIfc& repository) :
    m_alarms {this},
    m_repository {repository} {
    mediator.subscribe<AlarmAddedEvent>(this, &AlarmListCardViewModel::onAlarmAdded);
    mediator.subscribe<AlarmRemovedEvent>(this, &AlarmListCardViewModel::onAlarmRemoved);
    mediator.subscribe<AlarmUpdatedEvent>(this, &AlarmListCardViewModel::onAlarmUpdated);
}

AlarmListModel* AlarmListCardViewModel::alarmList() {
    return &m_alarms;
}

void AlarmListCardViewModel::activateAlarm(int alarmId) {
    m_repository.setAlarmState(alarmId, true);
}

void AlarmListCardViewModel::deactivateAlarm(int alarmId) {
    m_repository.setAlarmState(alarmId, false);
}

void AlarmListCardViewModel::onAlarmAdded(AlarmAddedEvent const& event) {
    auto viewModel = AlarmMapper::toViewModel(event.alarm);
    m_alarms.addAlarm(viewModel.release());
}

void AlarmListCardViewModel::onAlarmRemoved(AlarmRemovedEvent const& event) {
    AlarmItemViewModel* alarm = m_alarms.alarmById(event.id);
    if (alarm) {
        m_alarms.removeAlarm(alarm);
    }
}

void AlarmListCardViewModel::onAlarmUpdated(AlarmUpdatedEvent const& event) {
    auto viewModel = AlarmMapper::toViewModel(event.alarm);
    AlarmItemViewModel* existingAlarm = m_alarms.alarmById(event.alarm.id);
    if (existingAlarm) {
        existingAlarm->updateFrom(*viewModel);
    }
}
