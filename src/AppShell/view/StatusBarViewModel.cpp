#include "StatusBarViewModel.h"

StatusBarViewModel::StatusBarViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_networkStrength {-1},
    m_title {"Qlocky"},
    m_airplaneMode {false},
    m_lightMode {false},
    m_volumeType {VolumeType::Level::Mute} {
    // TODO register events for NetworkStatus, AirplaneMode, LightMode
}

void StatusBarViewModel::setNetworkState(bool enabled) {
    if (enabled && m_airplaneMode) {
        setAirplaneMode(false);
    }

    // TODO forward to service

    m_networkStrength = enabled ? 100 : -1;  // Simulate network strength
    setSsid(enabled ? "QlockyNetwork" : ""); // Simulate SSID

    emit networkStrengthChanged();
}

void StatusBarViewModel::setSsid(QString const& ssid) {
    if (m_ssid != ssid) {
        m_ssid = ssid;
        emit ssidChanged();
    }
}

void StatusBarViewModel::setAirplaneMode(bool enabled) {
    if (enabled) {
        setNetworkState(false);
    }

    // TODO forward to service

    if (m_airplaneMode != enabled) {
        m_airplaneMode = enabled;
        emit airplaneModeChanged();
    }
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