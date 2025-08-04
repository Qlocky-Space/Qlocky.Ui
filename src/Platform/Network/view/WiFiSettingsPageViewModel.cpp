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
}

void WiFiSettingsPageViewModel::setWifiEnabled(bool const enabled) {
    if (m_wifiEnabled != enabled) {
        m_wifiEnabled = enabled;
        emit wifiEnabledChanged();
        m_networkService.setWifiEnabled(enabled);
    }
}

void WiFiSettingsPageViewModel::startScan() {
    m_scanning = true;
    emit scanningChanged();

    m_networkService.startScan();
}

void WiFiSettingsPageViewModel::onCommunicationStatus(CommunicationStatusEvent const& event) {
    setWifiEnabled(event.getWifiMode());
}

void WiFiSettingsPageViewModel::onNetworkScanResult(NetworkScanResultEvent const& event) {
    m_scanning = false;
    emit scanningChanged();

    NetworkProfile const& profile {event.networkProfile()};

    auto networkViewModel = new WiFiNetworkViewModel();
    networkViewModel->setSsid(QString::fromStdString(profile.Ssid));
    networkViewModel->setSignalStrength(profile.SignalStrength);
    networkViewModel->setConnected(profile.IsConnected);

    m_networkListModel.addNetwork(networkViewModel);
    // TODO
}
