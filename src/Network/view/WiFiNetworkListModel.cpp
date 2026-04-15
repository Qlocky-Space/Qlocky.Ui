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

void WiFiNetworkListModel::addNetwork(NetworkProfile const& profile) {
    beginInsertRows(QModelIndex(), m_networks.size(), m_networks.size());

    WiFiNetworkViewModel* network = new WiFiNetworkViewModel();
    network->setSsid(QString::fromStdString(profile.Ssid));
    network->setSignalStrength(profile.SignalStrength);
    network->setConnected(profile.IsConnected);
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

void WiFiNetworkListModel::updateNetwork(NetworkProfile const& profile) {
    auto it = findNetworkBySsid(profile.Ssid);

    if (it != m_networks.end()) {
        (*it)->setSignalStrength(profile.SignalStrength);
        (*it)->setConnected(profile.IsConnected);

        int index = std::distance(m_networks.begin(), it);
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    }
    else {
        addNetwork(profile);
    }
}

void WiFiNetworkListModel::removeNetwork(std::string const& ssid) {
    auto it = findNetworkBySsid(ssid);

    if (it != m_networks.end()) {
        removeNetwork(std::distance(m_networks.begin(), it));
    }
}

void WiFiNetworkListModel::clearNetworks() {
    beginResetModel();
    qDeleteAll(m_networks);
    m_networks.clear();
    endResetModel();
}

QVector<WiFiNetworkViewModel*>::iterator WiFiNetworkListModel::findNetworkBySsid(std::string const& ssid) {
    return std::find_if(m_networks.begin(), m_networks.end(), [&ssid](WiFiNetworkViewModel* n) {
        return n->ssid() == QString::fromStdString(ssid);
    });
}
