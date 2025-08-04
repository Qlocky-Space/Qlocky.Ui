#ifndef WIFI_NETWORK_LIST_MODEL_H
#define WIFI_NETWORK_LIST_MODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "WiFiNetworkViewModel.h"

/**
 * WiFiNetworkListModel is a model that holds a list of Wi-Fi networks.
 * It provides methods to manage the list and notify views of changes.
 */
class WiFiNetworkListModel : public QAbstractListModel {
    Q_OBJECT

public:

    /**
     * @brief Roles for the Wi-Fi network model.
     * These roles are used to access specific properties of the Wi-Fi networks.
     */
    enum Roles {
        SsidRole = Qt::UserRole + 1,
        SignalStrengthRole,
        ConnectedRole
    };

    explicit WiFiNetworkListModel();
    ~WiFiNetworkListModel() final;

    /**
     * @see QAbstractListModel::rowCount
     */
    int rowCount(QModelIndex const& parent = QModelIndex()) const final;

    /**
     * @see QAbstractListModel::data
     */
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const final;

    /**
     * @see QAbstractListModel::roleNames
     */
    QHash<int, QByteArray> roleNames() const final;

    /**
     * Adds a Wi-Fi network to the model.
     * @param network The Wi-Fi network to add.
     */
    void addNetwork(WiFiNetworkViewModel* network);

    /**
     * Updates an existing Wi-Fi network in the model.
     * @param network The Wi-Fi network to update.
     */
    void updateNetwork(WiFiNetworkViewModel* network);

    /**
     * Removes a Wi-Fi network from the model.
     * @param network The Wi-Fi network to remove.
     */
    void removeNetwork(WiFiNetworkViewModel* network);

    /**
     * Clears all Wi-Fi networks from the model.
     */
    void clearNetworks();

private:

    void removeNetwork(int index);

    QVector<WiFiNetworkViewModel*> m_networks;
};

#endif