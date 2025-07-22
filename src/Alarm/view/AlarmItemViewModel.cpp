#include "AlarmItemViewModel.h"

AlarmItemViewModel::AlarmItemViewModel(uint32_t const id) :
    m_id {id},
    m_dueTime {},
    m_state {},
    m_displayName {} {
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

void AlarmItemViewModel::updateFrom(AlarmItemViewModel const& other) {
    m_id = other.getAlarmId();

    setDisplayName(other.getDisplayName());
    setState(other.getState());
    setDueTime(other.getDueTime());
    setRepeated(other.isRepeated());

    // @note: When adding new attributes to AlarmItemViewModel, add the mapping here.
}