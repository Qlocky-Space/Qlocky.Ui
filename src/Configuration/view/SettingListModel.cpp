#include "SettingListModel.h"

SettingListModel::SettingListModel() :
    QAbstractListModel {nullptr},
    m_items {} {
}

SettingListModel::~SettingListModel() {
    qDeleteAll(m_items);
    m_items.clear();
}

int SettingListModel::rowCount(QModelIndex const& parent) const {
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant SettingListModel::data(QModelIndex const& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_items.size()) {
        return QVariant();
    }

    SettingItemViewModel* item = m_items.at(index.row());
    switch (role) {
        case TitleRole:
            return item->title();
        case CategoryRole:
            return item->category();
        case PathRole:
            return item->path();
        case Qt::UserRole:
            return QVariant::fromValue(item);
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> SettingListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[CategoryRole] = "category";
    roles[PathRole] = "path";
    return roles;
}

void SettingListModel::addItem(SettingItemViewModel* item) {
    if (!item) {
        return;
    }

    qsizetype const index {m_items.size()};
    beginInsertRows(QModelIndex {}, index, index);
    m_items.append(item);
    endInsertRows();
}
