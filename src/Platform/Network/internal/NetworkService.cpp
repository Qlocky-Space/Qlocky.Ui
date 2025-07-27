#include "NetworkService.h"

#include <iostream>
#include <unistd.h>

#include "events/CommunicationStatusEvent.h"
#include "events/NetworkStatusEvent.h"
#include "NetworkStateMachine.h"

NetworkService::NetworkService(Mediator& mediator, PersistenceServiceIfc& persistenceService,
    NetworkDriverIfc& networkDriver) :
    m_mediator {mediator},
    m_persistency {persistenceService},
    m_stateMachine {mediator, networkDriver},
    m_airplaneMode {false} {

    networkDriver.attach(this);
}

void NetworkService::initialize() {
    bool const airplaneMode {getDatabase().getBool(AirplaneModeKey).valueOr(false)};
    bool const serviceEnabled {getDatabase().getBool(NetworkEnabledKey).valueOr(false)};

    // restore state from persistence
    setAirplaneMode(airplaneMode);
    if (serviceEnabled) {
        enable();
    }
    else {
        disable();
    }
}

void NetworkService::enable() {
    if (m_airplaneMode) {
        // Cannot enable network while airplane mode is on
        return;
    }

    m_stateMachine.enable();

    getDatabase().setBool(NetworkEnabledKey, true);
    sendCommunicationStatus();
}

void NetworkService::disable() {
    m_stateMachine.disable();

    getDatabase().setBool(NetworkEnabledKey, false);
    sendCommunicationStatus();
}

void NetworkService::setAirplaneMode(bool enabled) {
    m_airplaneMode = enabled;

    // If airplane mode is enabled, ensure service is disabled
    // to prevent network operations while in airplane mode.
    if (enabled) {
        m_stateMachine.disable();
    }

    getDatabase().setBool(AirplaneModeKey, m_airplaneMode);
    sendCommunicationStatus();
}

void NetworkService::onNetStatusChanged(PhyStatus const status) {
    // TODO implement handling of network status changes
}

void NetworkService::onScanCompleted(bool success) {
    std::cout << "Network scan completed: " << (success ? "Success" : "Failure") << std::endl;
    // m_networkDriver.fetchScanResults();
}

void NetworkService::onScanResultsAvailable(ScanResult& result) {
    std::cout << "Scan results available for SSID: " << result.ssid
              << " with signal strength: " << result.signalStrength << std::endl;

    // TODO implement handling of scan results
    // m_activeNetwork = NetworkInfo(result.ssid, result.signalStrength, true);
}

void NetworkService::sendCommunicationStatus() {
    bool const networkEnabled = m_stateMachine.currentState() != NetworkStates::DOWN;
    m_mediator.notify(CommunicationStatusEvent(m_airplaneMode, networkEnabled));
}
