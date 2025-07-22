#include "AlarmItemViewModel.h"

AlarmItemViewModel::AlarmItemViewModel(uint32_t const id) :
    m_id {id},
    m_dueTime {},
    m_state {},
    m_repeated {},
    m_displayName {},
    m_snoozeTime {},
    m_maxSnoozeCount {},
    m_snoozeCount {},
    m_daysOfWeek {DayOfWeekViewModel::Day::None} {
}

void AlarmItemViewModel::setDisplayName(QString const& displayName) {
    if (m_displayName != displayName) {
        m_displayName = displayName;
        emit displayNameChanged();
    }
}

void AlarmItemViewModel::setState(bool state) {
    if (m_state != state) {
        m_state = state;
        emit stateChanged();
    }
}

void AlarmItemViewModel::setDueTime(uint32_t const dueTime) {
    if (m_dueTime != dueTime) {
        m_dueTime = dueTime;
        emit dueTimeChanged();
    }
}

void AlarmItemViewModel::setRepeated(bool repeated) {
    if (m_repeated != repeated) {
        m_repeated = repeated;
        emit repeatedChanged();
    }
}

void AlarmItemViewModel::setSnoozeTime(uint32_t snoozeTime) {
    if (m_snoozeTime != snoozeTime) {
        m_snoozeTime = snoozeTime;
        emit snoozeTimeChanged();
    }
}

void AlarmItemViewModel::setMaxSnoozeCount(uint8_t maxSnoozeCount) {
    if (m_maxSnoozeCount != maxSnoozeCount) {
        m_maxSnoozeCount = maxSnoozeCount;
        emit maxSnoozeCountChanged();
    }
}

void AlarmItemViewModel::setSnoozeCount(uint8_t snoozeCount) {
    if (m_snoozeCount != snoozeCount) {
        m_snoozeCount = snoozeCount;
        emit snoozeCountChanged();
    }
}

void AlarmItemViewModel::setDaysOfWeek(DayOfWeekViewModel::Days daysOfWeek) {
    if (m_daysOfWeek != daysOfWeek) {
        m_daysOfWeek = daysOfWeek;
        emit daysOfWeekChanged();
    }
}

void AlarmItemViewModel::updateFrom(AlarmItemViewModel const& other) {
    m_id = other.getAlarmId();

    setDisplayName(other.getDisplayName());
    setState(other.getState());
    setDueTime(other.getDueTime());
    setRepeated(other.isRepeated());
    setSnoozeTime(other.snoozeTime());
    setMaxSnoozeCount(other.getMaxSnoozeCount());
    setSnoozeCount(other.getSnoozeCount());
    setDaysOfWeek(other.getDaysOfWeek());

    // @note: When adding new attributes to AlarmItemViewModel, add the mapping here.
}