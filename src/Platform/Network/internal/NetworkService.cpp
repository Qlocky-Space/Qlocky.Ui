#include "NetworkService.h"

#include <iostream>
#include <unistd.h>

#include "events/NetworkStatusEvent.h"

NetworkService::NetworkService(Mediator& mediator, PersistenceServiceIfc& persistenceService,
    NetworkDriverIfc& networkDriver) :
    m_mediator {mediator},
    m_persistency {persistenceService},
    m_networkDriver {networkDriver},
    m_activeNetwork {},
    m_airplaneMode {false},
    m_serviceEnabled {false} {

    m_networkDriver.attach(this);
}

void NetworkService::initialize() {
    bool const airplaneMode {getDatabase().getBool(AirplaneModeKey).valueOr(false)};
    bool const serviceEnabled {getDatabase().getBool(NetworkEnabledKey).valueOr(false)};

    setAirplaneMode(airplaneMode);
    setServiceEnable(serviceEnabled);
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

    setServiceEnable(true);
    // m_networkDriver.triggerScan();
    // sleep(5);
    m_networkDriver.fetchScanResults();
}

void NetworkService::disable() {
    if (!m_serviceEnabled) {
        // Already disabled, no action needed
        return;
    }

    setServiceEnable(false);
}

void NetworkService::setAirplaneMode(bool enabled) {
    m_airplaneMode = enabled;

    // If airplane mode is enabled, ensure service is disabled
    // to prevent network operations while in airplane mode.
    if (enabled && m_serviceEnabled) {
        disable();
    }

    getDatabase().setBool(AirplaneModeKey, m_airplaneMode);
}

void NetworkService::onNetStatusChanged(NetworkStatus const status) {
    // TODO implement handling of network status changes

    updateNetworkStatus();
}

void NetworkService::onScanCompleted(bool success) {
    std::cout << "Network scan completed: " << (success ? "Success" : "Failure") << std::endl;
    // m_networkDriver.fetchScanResults();
}

void NetworkService::onScanResultsAvailable(ScanResult& result) {
    std::cout << "Scan results available for SSID: " << result.ssid
              << " with signal strength: " << result.signalStrength << std::endl;

    // TODO implement handling of scan results
    m_activeNetwork = NetworkInfo(result.ssid, result.signalStrength, true);
}

void NetworkService::updateNetworkStatus() {
    constexpr int32_t disabledNetworkStrength = -1;

    // TODO remove demo

    std::string ssid = m_serviceEnabled && m_activeNetwork.isConnected() ? m_activeNetwork.getSsid() : "";
    int32_t networkStrength = m_serviceEnabled && m_activeNetwork.isConnected() ? m_activeNetwork.getSignalStrength() : disabledNetworkStrength;

    NetworkStatusEvent event {ssid, m_airplaneMode, m_serviceEnabled, networkStrength};
    m_mediator.notify(event);
}

void NetworkService::setServiceEnable(bool const enable) {
    if (enable == m_serviceEnabled) {
        // No change in service state
        return;
    }

    m_serviceEnabled = enable;

    auto const result {enable ? m_networkDriver.up("wlan0") : m_networkDriver.down()};
    if (result.isError()) {
        // TODO log error
        m_serviceEnabled = false;
        std::cerr << "Failed to change network service state: " << result.error() << std::endl;
    }

    getDatabase().setBool(NetworkEnabledKey, m_serviceEnabled);
    updateNetworkStatus();
}
