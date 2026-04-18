#include "StatusBarViewModel.h"

#include <algorithm>
#include <cmath>

StatusBarViewModel::StatusBarViewModel(Mediator& mediator, NetworkServiceIfc& networkService, NetworkRepositoryIfc& networkRepository, RadioPlayerIfc& radio, DisplayServiceIfc& displayService) :
    QObject {nullptr},
    m_networkService {networkService},
    m_networkRepository {networkRepository},
    m_radio {radio},
    m_displayService {displayService},
    m_title {"Qlocky"},
    m_ssid {""},
    m_networkStrength {-1},
    m_networkState {false},
    m_airplaneMode {false},
    m_lightMode {false},
    m_brightness {100.F},
    m_volume {100.F},
    m_volumeType {VolumeType::Level::Acoustic} {

    mediator.subscribe<WifiStatusEvent>(this, &StatusBarViewModel::updateWifiStatus);
    mediator.subscribe<ConnectionStatusEvent>(this, &StatusBarViewModel::updateConnectionStatus);
    mediator.subscribe<CommunicationStatusEvent>(this, &StatusBarViewModel::updateCommunicationStatus);
    mediator.subscribe<AudioOutputVolumeEvent>(this, &StatusBarViewModel::updateAudioOutputVolume);
    mediator.subscribe<DisplayBrightnessChangedEvent>(this, &StatusBarViewModel::updateDisplayBrightness);
}

void StatusBarViewModel::setNetworkState(bool enabled) {
    // just for user convenience, this will toggle the network state to on,
    // if airplane mode is enabled, it will disable it first
    if (enabled && m_airplaneMode) {
        setAirplaneMode(false);
    }

    m_networkService.setWifiEnabled(enabled);
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
    if (m_lightMode != enabled) {
        m_lightMode = enabled;
        emit lightModeChanged();
    }
}

void StatusBarViewModel::setBrightness(float value) {
    float const clamped = std::clamp(value, 0.0F, 100.0F);
    uint8_t const brightnessPercent = static_cast<uint8_t>(std::lround(clamped));
    m_displayService.setBrightnessPercent(brightnessPercent);
}

void StatusBarViewModel::setVolume(float value) {
    float const clamped = std::clamp(value, 0.0F, 100.0F);
    uint8_t const requested = static_cast<uint8_t>(std::lround(clamped));
    m_radio.setOutputVolume(requested);
}

void StatusBarViewModel::setVolumeType(VolumeType::Level type) {
    // TODO forward volume type to service, at the moment it is not clear which
    // service should be responsible for applying the volume type and how it should be applied
    // For now, just update the local state and notify the UI, without applying any actual changes to the system
    //   -> Maybe this feature is not as useful for this system as for smartphones because there are no notifications...

    // First proposal:
    // switch (type) {
    //     case VolumeType::Level::Mute:
    //         // TODO disable vibration service
    //         // TODO disable acoustic output
    //         // Question: What should happen with alarms?
    //         break;

    //     case VolumeType::Level::Vibration:
    //         // TODO enable vibration service
    //         // TODO enable acoustic output to user defined volumne
    //         break;

    //     case VolumeType::Level::Acoustic:
    //         // TODO disable vibration service
    //         // TODO enable acoustic output to user defined volumne

    //         break;
    // }

    if (m_volumeType != type) {
        m_volumeType = type;
        emit volumeTypeChanged();
    }
}

void StatusBarViewModel::updateWifiStatus(WifiStatusEvent const& event) {
    NetworkStateType::State networkState {toNetworkType(event.getWifiStatus())};

    // Reset SSID if the network is disabled
    if (networkState == NetworkStateType::State::Disabled || networkState == NetworkStateType::State::Disconnected) {
        setSsid("");
    }

    if (m_networkState != networkState) {
        m_networkState = networkState;
        emit networkStateChanged();
    }
}

void StatusBarViewModel::updateConnectionStatus(ConnectionStatusEvent const& event) {
    setSsid(QString::fromStdString(event.ssid()));

    if (m_networkStrength != event.signalStrength()) {
        m_networkStrength = event.signalStrength();
        emit networkStrengthChanged();
    }
}

void StatusBarViewModel::updateCommunicationStatus(CommunicationStatusEvent const& event) {
    if (m_airplaneMode != event.getAirplaneMode()) {
        m_airplaneMode = event.getAirplaneMode();
        emit airplaneModeChanged();
    }

    if (!event.getWifiMode()) {
        m_networkState = NetworkStateType::State::Disabled;

        // Reset the SSID when Wi-Fi mode is disabled
        setSsid("");
        emit networkStateChanged();
    }
}

void StatusBarViewModel::updateAudioOutputVolume(AudioOutputVolumeEvent const& event) {
    float const actualVolume = static_cast<float>(event.volumePercent());
    if (m_volume != actualVolume) {
        m_volume = actualVolume;
        emit volumeChanged();
    }
}

void StatusBarViewModel::updateDisplayBrightness(DisplayBrightnessChangedEvent const& event) {
    float const actualBrightness = static_cast<float>(event.brightnessPercent());
    if (m_brightness != actualBrightness) {
        m_brightness = actualBrightness;
        emit brightnessChanged();
    }
}
