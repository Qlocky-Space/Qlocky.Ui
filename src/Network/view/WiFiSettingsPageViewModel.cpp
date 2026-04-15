#include "WiFiSettingsPageViewModel.h"

WiFiSettingsPageViewModel::WiFiSettingsPageViewModel(Mediator& mediator, NetworkServiceIfc& networkService, WiFiNetworkListModel& networkListModel) :
    QObject {nullptr},
    m_mediator {mediator},
    m_networkService {networkService},
    m_networkListModel {networkListModel},
    m_wifiEnabled {false},
    m_scanning {false} {
    mediator.subscribe<NetworkScanResultEvent>(this, &WiFiSettingsPageViewModel::onNetworkScanResult);
    mediator.subscribe<CommunicationStatusEvent>(this, &WiFiSettingsPageViewModel::onCommunicationStatus);
    mediator.subscribe<NetworkScanEvent>(this, &WiFiSettingsPageViewModel::onNetworkScanEvent);
    mediator.subscribe<ConnectionStatusEvent>(this, &WiFiSettingsPageViewModel::onConnectionStatus);
}

void WiFiSettingsPageViewModel::startScan() {
    if (m_scanning) {
        return; // Already scanning
    }

    m_networkListModel.clearNetworks();
    m_networkService.startScan();
}

void WiFiSettingsPageViewModel::onCommunicationStatus(CommunicationStatusEvent const& event) {
    setWifiEnabled(event.getWifiMode());
}

void WiFiSettingsPageViewModel::onNetworkScanResult(NetworkScanResultEvent const& event) {
    NetworkProfile const& profile {event.networkProfile()};
    m_networkListModel.updateNetwork(event.networkProfile());
}

void WiFiSettingsPageViewModel::onNetworkScanEvent(NetworkScanEvent const& event) {
    setScanning(event.isScanning());
}

void WiFiSettingsPageViewModel::onConnectionStatus(ConnectionStatusEvent const& event) {
    // required to update the connected state
    m_networkListModel.updateNetwork(event.networkProfile());
}

void WiFiSettingsPageViewModel::setWifiEnabled(bool const enabled) {
    if (m_wifiEnabled == enabled) {
        return;
    }

    m_wifiEnabled = enabled;
    emit wifiEnabledChanged();

    m_networkService.setWifiEnabled(enabled);

    // additional events, depending on the state of Wi-Fi
    if (enabled) {
        startScan();
    }
    else {
        m_networkListModel.clearNetworks();
    }
}

void WiFiSettingsPageViewModel::setScanning(bool scanning) {
    if (m_scanning != scanning) {
        m_scanning = scanning;
        emit scanningChanged();
    }
}
