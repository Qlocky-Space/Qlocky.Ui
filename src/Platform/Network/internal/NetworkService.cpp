#include "NetworkService.h"

#include <iostream>

#include "events/CommunicationStatusEvent.h"
#include "NetworkProfileMapper.h"
#include "NetworkStateMachine.h"

NetworkService::NetworkService(Mediator& mediator, NetworkRepositoryIfc& repository,
    NetworkDriverIfc& networkDriver) :
    m_mediator {mediator},
    m_repository {repository},
    m_stateMachine {mediator, networkDriver, repository},
    m_networkDriver {networkDriver},
    m_airplaneMode {false} {

    networkDriver.attach(&m_stateMachine);
}

void NetworkService::initialize() {
    bool const airplaneMode {m_repository.getAirplaneMode()};
    bool const serviceEnabled {m_repository.getNetworkEnabled()};

    // restore state from persistence
    setAirplaneMode(airplaneMode);
    setWifiEnabled(serviceEnabled);

    // because the state machine is initialized all events
    // must be forced to ensure listeners are notified
    m_stateMachine.forceEvents();
}

void NetworkService::setAirplaneMode(bool enabled) {
    m_airplaneMode = enabled;
    m_repository.setAirplaneMode(enabled);

    // If airplane mode is enabled, ensure service is disabled
    // to prevent network operations while in airplane mode.
    if (enabled) {
        m_stateMachine.disable();
    }

    sendCommunicationStatusEvent();
}

void NetworkService::setWifiEnabled(bool enabled) {
    if (enabled && m_airplaneMode) {
        // Cannot enable Wi-Fi while airplane mode is on
        return;
    }

    m_repository.setNetworkEnabled(enabled);

    if (enabled) {
        m_stateMachine.enable();
    }
    else {
        m_stateMachine.disable();
    }

    sendCommunicationStatusEvent();
}

void NetworkService::startScan() {
    m_networkDriver.triggerScan();
}

void NetworkService::connectTo(NetworkProfileNew const& profile) {
    // Save the profile to persistence
    NetworkProfileEntity profileEntity = NetworkProfileMapper::toEntity(profile);
    m_repository.addProfile(profileEntity);
    m_networkDriver.registerNetwork(NetworkProfileMapper::toNetworkInfo(profileEntity));

    connectTo(profileEntity.ssid);
}

void NetworkService::connectTo(std::string const& ssid) {
    // Fetch the profile from persistence
    std::optional<NetworkProfileEntity> profile {m_repository.getProfileBySsid(ssid)};

    m_repository.selectNetwork(ssid);

    if (profile.has_value()) {
        m_stateMachine.connectTo(profile.value());
    }
    else {
        std::cerr << "Profile with SSID " << ssid << " not found." << std::endl;
    }
}

void NetworkService::disconnect() {
    m_stateMachine.disconnect();
}

void NetworkService::sendCommunicationStatusEvent() {
    bool const wifiMode {m_stateMachine.currentState() != NetworkStates::DOWN};
    CommunicationStatusEvent const event(m_airplaneMode, wifiMode);

    m_mediator.notify(event);
}
