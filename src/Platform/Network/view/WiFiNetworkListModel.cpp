#include "WiFiNetworkListModel.h"

WiFiNetworkListModel::WiFiNetworkListModel() {
}

WiFiNetworkListModel::~WiFiNetworkListModel() {
    clearNetworks();
}

int WiFiNetworkListModel::rowCount(QModelIndex const& parent) const {
    Q_UNUSED(parent);
    return m_networks.size();
}

QVariant WiFiNetworkListModel::data(QModelIndex const& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_networks.size()) {
        return QVariant();
    }

    WiFiNetworkViewModel* network = m_networks.at(index.row());
    switch (role) {
        case SsidRole:
            return network->ssid();
        case SignalStrengthRole:
            return network->signalStrength();
        case ConnectedRole:
            return network->connected();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> WiFiNetworkListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[SsidRole] = "ssid";
    roles[SignalStrengthRole] = "signalStrength";
    roles[ConnectedRole] = "connected";
    return roles;
}

void WiFiNetworkListModel::addNetwork(WiFiNetworkViewModel* network) {
    beginInsertRows(QModelIndex(), m_networks.size(), m_networks.size());
    m_networks.append(network);
    endInsertRows();
}

void WiFiNetworkListModel::removeNetwork(int index) {
    if (index < 0 || index >= m_networks.size()) {
        return;
    }
    beginRemoveRows(QModelIndex(), index, index);
    delete m_networks.takeAt(index);
    endRemoveRows();
}

void WiFiNetworkListModel::updateNetwork(WiFiNetworkViewModel* network) {
    int index = m_networks.indexOf(network);
    if (index != -1) {
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    }
}

void WiFiNetworkListModel::removeNetwork(WiFiNetworkViewModel* network) {
    int index = m_networks.indexOf(network);
    if (index != -1) {
        removeNetwork(index);
    }
}

void WiFiNetworkListModel::clearNetworks() {
    beginResetModel();
    qDeleteAll(m_networks);
    m_networks.clear();
    endResetModel();
}
