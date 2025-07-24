#include "StatusBarViewModel.h"

StatusBarViewModel::StatusBarViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_networkStrength {-1},
    m_title {"Qlocky"},
    m_airplaneMode {false},
    m_lightMode {false} {
    // TODO register events for NetworkStatus, AirplaneMode, LightMode
}

void StatusBarViewModel::setNetworkState(bool enabled) {
    if (enabled && m_airplaneMode) {
        setAirplaneMode(false);
    }

    // TODO forward to service

    m_networkStrength = enabled ? 100 : -1; // Simulate network strength
    emit networkStrengthChanged();
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