#include "NetworkStateMachine.h"

#include "events/ConnectionStatusEvent.h"
#include "events/WifiStatusEvent.h"
#include "NetworkProfileMapper.h"

void NetworkStateMachine::forceEvents() {
    sendNetworkStatus();
    if (currentState() == NetworkStates::CONNECTED) {
        sendConnectionStatus();
    }

    runStateMachine();
}

void NetworkStateMachine::disable() {
    m_disabled = true;
    runStateMachine();
}

void NetworkStateMachine::enable() {
    m_enabled = true;
    runStateMachine();
}

void NetworkStateMachine::connectTo(NetworkProfileEntity const& profile) {
    m_activeProfile = {};
    m_activeProfile.Id = profile.id;
    m_activeProfile.Ssid = profile.ssid;

    m_connecting = true;

    runStateMachine();
}

void NetworkStateMachine::disconnect() {
    m_disconnect = true;

    runStateMachine();
}

void NetworkStateMachine::onInterfaceStatusChanged(NetworkIfStatus const status) {
    m_connected = (status == NetworkIfStatus::CONNECTED);
    m_lost = (status == NetworkIfStatus::DISCONNECTED);
    m_connecting = (status == NetworkIfStatus::CONNECTING);

    runStateMachine();
}

void NetworkStateMachine::onScanCompleted(bool success) {
    if (success) {
        // get the results, will trigger onScanResultsAvailable
        m_networkDriver.fetchScanResults();
    }
    else {
        setErrorCode(NetworkDriverErrorCode::ERROR_SCAN_FAILED);
    }

    runStateMachine();
}

void NetworkStateMachine::onScanResultsAvailable(ScanResult& result) {
    if (result.ssid != m_activeProfile.Ssid) {
        return;
    }

    m_activeProfile.IsConnected = true;
    m_activeProfile.SignalStrength = result.signalStrength;

    runStateMachine();
}

void NetworkStateMachine::onError(int32_t errorCode) {
    m_errorCode = errorCode;
    runStateMachine();
}

void NetworkStateMachine::onTransition(NetworkStates const state) {
    switch (state) {
        case NetworkStates::DOWN:
            m_enabled = transitionByCondition(m_enabled, NetworkStates::UP);
            break;
        case NetworkStates::UP:
            m_connecting = transitionByCondition(m_connecting, NetworkStates::CONNECTING);
            transitionOnDisabled();
            transitionOnError();
            break;
        case NetworkStates::CONNECTING:
            m_connected = transitionByCondition(m_connected, NetworkStates::CONNECTED);
            m_disconnect = transitionByCondition(m_disconnect, NetworkStates::UP);
            m_lost = transitionByCondition(m_lost, NetworkStates::UP);
            transitionOnDisabled();
            transitionOnError();
            break;
        case NetworkStates::CONNECTED:
            m_lost = transitionByCondition(m_lost, NetworkStates::CONNECTING);
            m_disconnect = transitionByCondition(m_disconnect, NetworkStates::UP);
            transitionOnDisabled();
            transitionOnError();
            break;
        case NetworkStates::ERROR:
            transitionOnDisabled();
            break;
        default:
            break;
    }
}

void NetworkStateMachine::onEnterState(NetworkStates const state) {
    switch (state) {
        case NetworkStates::DOWN:
            // If shutdown has error, ignore it
            m_networkDriver.down();
            m_activeProfile = {};
            sendNetworkStatus();
            break;
        case NetworkStates::UP:
            onUpEntered();
            break;
        case NetworkStates::CONNECTING:
            m_networkDriver.connectTo(m_activeProfile.Ssid)
                .onError(m_errorCallback)
                .onSuccess(m_sendStatusCallback);
            break;
        case NetworkStates::CONNECTED:
            sendNetworkStatus();
            break;
        case NetworkStates::ERROR:
            sendNetworkStatus();
            break;
        default:
            break;
    }
}

void NetworkStateMachine::onLeaveState(NetworkStates const state) {
    switch (state) {
        case NetworkStates::DOWN:
            m_networkDriver.up(DEFAULT_INTERFACE_NAME)
                .onError(m_errorCallback)
                .onSuccess(m_sendStatusCallback);
            break;
        case NetworkStates::ERROR:
            m_errorCode = 0; // Reset error code
            break;

        default:
            break;
    }
}

void NetworkStateMachine::onRunState(NetworkStates const state) {
    switch (state) {
        case NetworkStates::CONNECTING:
        case NetworkStates::CONNECTED:
            sendConnectionStatus();
            break;
        default:
            break;
    }
}

void NetworkStateMachine::onUpEntered() {
    // ensure in UP state, the interface is disconnected
    m_networkDriver.disconnect()
        .onError(m_errorCallback)
        .onSuccess(m_sendStatusCallback);

    // Register all saved networks
    auto profiles = m_repository.getAllProfiles();
    for (auto const& profile : profiles) {
        m_networkDriver.registerNetwork(NetworkProfileMapper::toNetworkInfo(profile));
    }

    // If a profile is set to auto-connect, connect to it
    auto lastNetwork = m_repository.getLastNetwork();
    if (lastNetwork.has_value()) {
        // If the last network is already connected, skip connecting
        // to avoid unnecessary reconnections.
        bool const alreadyConnected {m_activeProfile.Ssid == lastNetwork->ssid};

        if (!alreadyConnected && lastNetwork->autoConnect) {
            connectTo(lastNetwork.value());
        }
    }
}

void NetworkStateMachine::transitionOnError() {
    if (m_errorCode != 0) {
        setNextState(NetworkStates::ERROR);
    }
}

void NetworkStateMachine::transitionOnDisabled() {
    if (m_disabled) {
        setNextState(NetworkStates::DOWN);
    }
}

void NetworkStateMachine::sendNetworkStatus() {
    WifiStatus status {};

    switch (currentState()) {
        case NetworkStates::DOWN:
            status = WifiStatus::DOWN;
            break;
        case NetworkStates::UP:
            status = WifiStatus::UP;
            break;
        case NetworkStates::CONNECTING:
            status = WifiStatus::CONNECTING;
            break;
        case NetworkStates::CONNECTED:
            status = WifiStatus::CONNECTED;
            break;
        case NetworkStates::ERROR:
            status = WifiStatus::ERROR;
            break;
        default:
            status = WifiStatus::ERROR;
            break;
    }

    m_mediator.notify(WifiStatusEvent(status));
}

void NetworkStateMachine::sendConnectionStatus() {
    ConnectionStatusEvent event {m_activeProfile.Id};
    event.setFrom(m_activeProfile);

    m_mediator.notify(event);
}
