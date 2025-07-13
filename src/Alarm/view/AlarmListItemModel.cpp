#include "AlarmListItemModel.h"

AlarmListItemModel::AlarmListItemModel() :
    m_time {},
    m_active {},
    m_label {} {
}

void AlarmListItemModel::setLabel(QString const& label) {
    if (m_label != label) {
        m_label = label;
        emit labelChanged();
    }
}

void AlarmListItemModel::setActive(bool active) {
    if (m_active != active) {
        m_active = active;
        emit activeChanged();
    }
}

void AlarmListItemModel::setTime(QDateTime const& time) {
    if (m_time != time) {
        m_time = time;
        emit timeChanged();
    }
}
