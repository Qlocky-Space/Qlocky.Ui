#include "AlarmItemViewModel.h"

AlarmItemViewModel::AlarmItemViewModel(int const id) :
    m_id {id},
    m_time {},
    m_active {},
    m_label {} {
}

void AlarmItemViewModel::setLabel(QString const& label) {
    if (m_label != label) {
        m_label = label;
        emit labelChanged();
    }
}

void AlarmItemViewModel::setActive(bool active) {
    if (m_active != active) {
        m_active = active;
        emit activeChanged();
    }
}

void AlarmItemViewModel::setTime(QDateTime const& time) {
    if (m_time != time) {
        m_time = time;
        emit timeChanged();
    }
}
