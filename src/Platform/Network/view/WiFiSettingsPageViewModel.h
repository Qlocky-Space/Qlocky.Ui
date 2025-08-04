#ifndef WIFI_SETTINGS_PAGE_VIEW_MODEL_H
#define WIFI_SETTINGS_PAGE_VIEW_MODEL_H

#include <Mediator.h>
#include <QObject>

#include "events/CommunicationStatusEvent.h"
#include "events/NetworkScanEvent.h"
#include "events/NetworkScanResultEvent.h"
#include "NetworkServiceIfc.h"
#include "WiFiNetworkListModel.h"

/**
 * ViewModel for Wi-Fi settings page.
 * This class handles the logic for managing Wi-Fi settings and interactions with the network service.
 */
class WiFiSettingsPageViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel* networks READ networks CONSTANT)
    Q_PROPERTY(bool wifiEnabled READ wifiEnabled WRITE setWifiEnabled NOTIFY wifiEnabledChanged)
    Q_PROPERTY(bool scanning MEMBER m_scanning NOTIFY scanningChanged)

public:

    explicit WiFiSettingsPageViewModel(Mediator& mediator, NetworkServiceIfc& networkService, WiFiNetworkListModel& networkListModel);
    ~WiFiSettingsPageViewModel() final = default;

    /**
     * Gets the list of Wi-Fi networks.
     * @return The model containing the list of Wi-Fi networks.
     */
    QAbstractListModel* networks() {
        return &m_networkListModel;
    }

    /**
     * Gets the current Wi-Fi enabled state.
     * @return True if Wi-Fi is enabled, false otherwise.
     */
    bool wifiEnabled() const {
        return m_wifiEnabled;
    }

    /**
     * Sets the Wi-Fi enabled state.
     * @param enabled True to enable Wi-Fi, false to disable it.
     */
    void setWifiEnabled(bool const enabled);

    /**
     * Starts a network scan.
     */
    Q_INVOKABLE void startScan();

signals:
    void wifiEnabledChanged();
    void scanningChanged();

private:

    void setScanning(bool scanning);

    void onNetworkScanResult(NetworkScanResultEvent const& event);
    void onCommunicationStatus(CommunicationStatusEvent const& event);
    void onNetworkScanEvent(NetworkScanEvent const& event);

    Mediator& m_mediator;
    NetworkServiceIfc& m_networkService;
    WiFiNetworkListModel& m_networkListModel;

    bool m_wifiEnabled;
    bool m_scanning;
};

#endif