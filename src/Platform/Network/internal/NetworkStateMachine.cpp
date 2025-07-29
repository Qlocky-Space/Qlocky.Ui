#include "NetworkStateMachine.h"

#include <iostream>

#include "events/ConnectionStatusEvent.h"
#include "events/WifiStatusEvent.h"

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
    m_activeProfile.Id = profile.id;
    m_activeProfile.Ssid = profile.ssid;
    m_activeProfile.SignalStrength = 0;
    m_activeProfile.IsConnected = false;

    m_connecting = true;

    runStateMachine();
}

void NetworkStateMachine::disconnect() {
    m_disconnect = true;

    runStateMachine();
}

void NetworkStateMachine::onInterfaceStatusChanged(NetworkIfStatus const status) {
    std::string statusName;
    switch (status) {
        case NetworkIfStatus::DISCONNECTED:
            statusName = "DISCONNECTED";
            break;
        case NetworkIfStatus::CONNECTED:
            statusName = "CONNECTED";
            break;
        case NetworkIfStatus::CONNECTING:
            statusName = "CONNECTING";
            break;
    }

    std::cout << "NSM - Interface status changed: " << statusName << std::endl;

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
    std::string stateName;
    switch (state) {
        case NetworkStates::DOWN:
            stateName = "DOWN";
            break;
        case NetworkStates::UP:
            stateName = "UP";
            break;
        case NetworkStates::CONNECTING:
            stateName = "CONNECTING";
            break;
        case NetworkStates::CONNECTED:
            stateName = "CONNECTED";
            break;
        case NetworkStates::ERROR:
            stateName = "ERROR";
            break;
        default:
            stateName = "UNKNOWN";
            break;
    }

    std::cout << "NSM - Entering state: " << stateName << std::endl;

    switch (state) {
        case NetworkStates::DOWN:
            // If shutdown has error, ignore it
            m_networkDriver.down();
            sendNetworkStatus();
            break;
        case NetworkStates::UP:
            sendNetworkStatus();
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
    std::cout << "Leaving state: " << static_cast<int>(state) << std::endl;

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
    std::string statusName {};

    switch (currentState()) {
        case NetworkStates::DOWN:
            status = WifiStatus::DOWN;
            statusName = "DOWN";
            break;
        case NetworkStates::UP:
            status = WifiStatus::UP;
            statusName = "UP";
            break;
        case NetworkStates::CONNECTING:
            status = WifiStatus::CONNECTING;
            statusName = "CONNECTING";
            break;
        case NetworkStates::CONNECTED:
            status = WifiStatus::CONNECTED;
            statusName = "CONNECTED";
            break;
        case NetworkStates::ERROR:
            status = WifiStatus::ERROR;
            statusName = "ERROR";
            break;
        default:
            status = WifiStatus::ERROR;
            statusName = "UNKNOWN";
            break;
    }

    std::cout << "NSM - Sending wifi status: " << statusName << std::endl;
    m_mediator.notify(WifiStatusEvent(status));
}

void NetworkStateMachine::sendConnectionStatus() {
    ConnectionStatusEvent event {m_activeProfile.Id};
    event.setFrom(m_activeProfile);

    std::cout << "NSM - Sending connection status" << std::endl;
    m_mediator.notify(event);
}
