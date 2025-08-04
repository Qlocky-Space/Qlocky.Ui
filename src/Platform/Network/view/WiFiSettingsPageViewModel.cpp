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
}

void WiFiSettingsPageViewModel::startScan() {
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

void WiFiSettingsPageViewModel::setWifiEnabled(bool const enabled) {
    if (m_wifiEnabled != enabled) {
        m_wifiEnabled = enabled;
        emit wifiEnabledChanged();
        m_networkService.setWifiEnabled(enabled);
    }
}

void WiFiSettingsPageViewModel::setScanning(bool scanning) {
    if (m_scanning != scanning) {
        m_scanning = scanning;
        emit scanningChanged();
    }
}
