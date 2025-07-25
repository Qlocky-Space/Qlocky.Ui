#include "StatusBarViewModel.h"

StatusBarViewModel::StatusBarViewModel(Mediator& mediator, NetworkServiceIfc& networkService) :
    QObject {nullptr},
    m_networkService {networkService},
    m_title {"Qlocky"},
    m_ssid {""},
    m_networkStrength {-1},
    m_airplaneMode {false},
    m_lightMode {false},
    m_brightness {100.F},
    m_volume {100.F},
    m_volumeType {VolumeType::Level::Mute} {

    mediator.subscribe<NetworkStatusEvent>(this, &StatusBarViewModel::updateNetworkStatus);
    // TODO register events for LightMode, AudioVolume, Brightness, etc.
}

void StatusBarViewModel::setNetworkState(bool enabled) {
    // just for user convenience, this will toggle the network state to on,
    // if airplane mode is enabled, it will disable it first
    if (enabled && m_airplaneMode) {
        setAirplaneMode(false);
    }

    if (enabled) {
        m_networkService.enable();
    }
    else {
        m_networkService.disable();
    }
}

void StatusBarViewModel::setSsid(QString const& ssid) {
    if (m_ssid != ssid) {
        m_ssid = ssid;
        emit ssidChanged();
    }
}

void StatusBarViewModel::setAirplaneMode(bool enabled) {
    m_networkService.setAirplaneMode(enabled);
}

void StatusBarViewModel::setLightMode(bool enabled) {
    // TODO forward to service

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

void StatusBarViewModel::updateNetworkStatus(NetworkStatusEvent const& event) {
    setSsid(QString::fromStdString(event.ssid()));

    if (m_networkStrength != event.networkStrength()) {
        m_networkStrength = event.networkStrength();
        emit networkStrengthChanged();
    }

    if (m_airplaneMode != event.airplaneMode()) {
        m_airplaneMode = event.airplaneMode();
        emit airplaneModeChanged();
    }
}