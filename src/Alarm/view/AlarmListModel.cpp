#include "AlarmListModel.h"

AlarmListModel::AlarmListModel(QObject* parent) :
    QAbstractListModel {parent},
    m_alarms {} {
}

int AlarmListModel::rowCount(QModelIndex const& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_alarms.size();
}

QVariant AlarmListModel::data(QModelIndex const& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_alarms.size()) {
        return {};
    }

    AlarmItemViewModel* alarm {m_alarms.at(index.row())};

    switch (role) {
        case AlarmRole:
            return QVariant::fromValue(alarm);
        default:
            return {};
    }
}

QHash<int, QByteArray> AlarmListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[AlarmRole] = "alarm";
    return roles;
}

void AlarmListModel::addAlarm(AlarmItemViewModel* alarm) {
    if (!alarm) {
        return;
    }
    qsizetype const index {m_alarms.size()};
    beginInsertRows(QModelIndex {}, index, index);
    m_alarms.append(alarm);
    endInsertRows();
}

void AlarmListModel::removeAlarm(AlarmItemViewModel* alarm) {
    if (!alarm) {
        return;
    }
    qsizetype index {m_alarms.indexOf(alarm)};
    if (index < 0) {
        return;
    }
    beginRemoveRows(QModelIndex {}, index, index);
    m_alarms.removeAt(index);
    endRemoveRows();
}

AlarmItemViewModel* AlarmListModel::alarmById(int id) const {
    for (auto* alarm : m_alarms) {
        if (alarm->getAlarmId() == id) {
            return alarm;
        }
    }
    return nullptr;
}