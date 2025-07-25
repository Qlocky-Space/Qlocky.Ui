#include "NetworkService.h"

#include "events/NetworkStatusEvent.h"

NetworkService::NetworkService(Mediator& mediator) :
    m_mediator {mediator},
    m_airplaneMode {false},
    m_serviceEnabled {false} {
}

void NetworkService::enable() {
    if (m_airplaneMode) {
        // Cannot enable network while airplane mode is on
        return;
    }

    if (m_serviceEnabled) {
        // Already enabled, no action needed
        return;
    }

    m_serviceEnabled = true;

    updateNetworkStatus();
}

void NetworkService::disable() {
    if (!m_serviceEnabled) {
        // Already disabled, no action needed
        return;
    }

    m_serviceEnabled = false;

    updateNetworkStatus();
}

void NetworkService::setAirplaneMode(bool enabled) {
    m_airplaneMode = enabled;

    // If airplane mode is enabled, ensure service is disabled
    // to prevent network operations while in airplane mode.
    if (enabled && m_serviceEnabled) {
        disable();
    }

    updateNetworkStatus();
}

void NetworkService::updateNetworkStatus() {
    constexpr int32_t disabledNetworkStrength = -1;

    // TODO remove demo
    std::string ssid = m_serviceEnabled ? "ConnectedNetwork" : "";
    int32_t networkStrength = m_serviceEnabled ? 75 : disabledNetworkStrength;

    NetworkStatusEvent event {ssid, m_airplaneMode, networkStrength};
    m_mediator.notify(event);
}
