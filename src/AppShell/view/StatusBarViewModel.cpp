#include "StatusBarViewModel.h"

#include <iostream>

namespace {
constexpr NetworkStateType::State toType(WifiStatus status) {
    switch (status) {
        case WifiStatus::UP:
            return NetworkStateType::State::Disconnected;
        case WifiStatus::DOWN:
            return NetworkStateType::State::Disabled;
        case WifiStatus::CONNECTING:
            return NetworkStateType::State::Searching;
        case WifiStatus::CONNECTED:
            return NetworkStateType::State::Connected;
        case WifiStatus::ERROR:
            return NetworkStateType::State::Error;
        default:
            return NetworkStateType::State::Error;
    }
}
} // namespace

StatusBarViewModel::StatusBarViewModel(Mediator& mediator, NetworkServiceIfc& networkService, NetworkRepositoryIfc& networkRepository) :
    QObject {nullptr},
    m_networkService {networkService},
    m_networkRepository {networkRepository},
    m_title {"Qlocky"},
    m_ssid {""},
    m_networkStrength {-1},
    m_networkState {false},
    m_airplaneMode {false},
    m_lightMode {false},
    m_brightness {100.F},
    m_volume {100.F},
    m_volumeType {VolumeType::Level::Mute} {

    mediator.subscribe<WifiStatusEvent>(this, &StatusBarViewModel::updateWifiStatus);
    mediator.subscribe<NetworkScanResultEvent>(this, &StatusBarViewModel::updateNetworkScanResult);
    mediator.subscribe<ConnectionStatusEvent>(this, &StatusBarViewModel::updateConnectionStatus);
    mediator.subscribe<CommunicationStatusEvent>(this, &StatusBarViewModel::updateCommunicationStatus);

    // TODO register events for LightMode, AudioVolume, Brightness, etc.
}

void StatusBarViewModel::setNetworkState(bool enabled) {
    // just for user convenience, this will toggle the network state to on,
    // if airplane mode is enabled, it will disable it first
    if (enabled && m_airplaneMode) {
        setAirplaneMode(false);
    }

    std::cout << "Status Bar - Setting network state to " << (enabled ? "enabled" : "disabled") << std::endl;
    m_networkService.setWifiEnabled(enabled);
}

void StatusBarViewModel::setSsid(QString const& ssid) {
    if (m_ssid != ssid) {
        m_ssid = ssid;
        emit ssidChanged();
    }
}

void StatusBarViewModel::setAirplaneMode(bool enabled) {
    std::cout << "Status Bar - Start Scan (DEMO)" << std::endl;
    m_networkService.startScan();

    // m_networkService.setAirplaneMode(enabled);
}

void StatusBarViewModel::setLightMode(bool enabled) {
    if (enabled) {
        // TODO forward to service
        auto profiles {m_networkRepository.getAllProfiles()};
        if (profiles.empty()) {
            std::cout << "Status Bar - No saved networks found, creating a new profile." << std::endl;

            NetworkProfileNew profile {};
            profile.Ssid = "XXXXXXXXX";
            profile.Psk = "XXXXXXXXXX";
            m_networkService.connectTo(profile);
        }
        else {
            std::cout << "Status Bar - Connecting to the first saved network: " << profiles.front().ssid << std::endl;

            m_networkService.connectTo(profiles.front().ssid);
        }
    }
    else {
        std::cout << "Status Bar - Disconnecting from network." << std::endl;
        m_networkService.disconnect();
    }

    if (m_lightMode != enabled) {
        m_lightMode = enabled;
        emit lightModeChanged();
    }
}

void StatusBarViewModel::setBrightness(float value) {
    // TODO forward to service

    if (m_brightness != value) {
        m_brightness = value;
        emit brightnessChanged();
    }
}

void StatusBarViewModel::setVolume(float value) {
    // TODO forward to service

    if (m_volume != value) {
        m_volume = value;
        emit volumeChanged();
    }
}

void StatusBarViewModel::setVolumeType(VolumeType::Level type) {
    // TODO forward to service

    if (m_volumeType != type) {
        m_volumeType = type;
        emit volumeTypeChanged();
    }
}

void StatusBarViewModel::updateWifiStatus(WifiStatusEvent const& event) {
    NetworkStateType::State networkState {toType(event.getWifiStatus())};

    std::cout << "Status Bar - Network state changed to: " << static_cast<int>(networkState) << std::endl;
    if (m_networkState != networkState) {
        m_networkState = networkState;
        emit networkStateChanged();
    }
}

void StatusBarViewModel::updateConnectionStatus(ConnectionStatusEvent const& event) {
    std::cout << "Status Bar - Network SSID: " << event.ssid() << std::endl;
    std::cout << "Status Bar - Network Strength: " << event.signalStrength() << std::endl;

    setSsid(QString::fromStdString(event.ssid()));

    if (m_networkStrength != event.signalStrength()) {
        m_networkStrength = event.signalStrength();
        emit networkStrengthChanged();
    }
}

void StatusBarViewModel::updateNetworkScanResult(NetworkScanResultEvent const& event) {
    // Handle network scan results if needed
    // For now, we just log that the scan was completed
    std::cout << "Status Bar - Network scan result received: " << event.networkProfile().Ssid << std::endl;
}

void StatusBarViewModel::updateCommunicationStatus(CommunicationStatusEvent const& event) {
    if (m_airplaneMode != event.getAirplaneMode()) {
        m_airplaneMode = event.getAirplaneMode();
        emit airplaneModeChanged();
    }

    if (!event.getWifiMode()) {
        m_networkState = NetworkStateType::State::Disabled;

        setSsid("");
        emit networkStateChanged();
    }
}
