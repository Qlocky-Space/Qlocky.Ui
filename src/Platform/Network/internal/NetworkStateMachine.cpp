#include "NetworkStateMachine.h"

#include <iostream>

#include "events/NetworkStatusEvent.h"

void NetworkStateMachine::disable() {
    m_disabled = true;
    runStateMachine();
}

void NetworkStateMachine::enable() {
    m_enabled = true;
    runStateMachine();
}

void NetworkStateMachine::startScan() {
    m_scanning = true;
    runStateMachine();
}

void NetworkStateMachine::connectTo(std::string const& ssid) {
    m_networkInfo.Ssid = ssid;
    m_connecting = true;

    runStateMachine();
}

void NetworkStateMachine::onScanCompleted(bool foundResult) {
    if (foundResult) {
        // if SSID is set, try to connect to it
        m_connecting = !m_networkInfo.Ssid.empty();
    }
    else {
        m_scanDone = true;
    }

    runStateMachine();
}

void NetworkStateMachine::onNetworkStateChanged(NetworkInfo const& info) {
    if (currentState() != NetworkStates::CONNECTED) {
        return;
    }

    m_networkInfo = info;
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
            m_scanning = transitionByCondition(m_scanning, NetworkStates::SCANNING);
            m_connecting = transitionByCondition(m_connecting, NetworkStates::CONNECTED);
            transitionOnDisabled();
            transitionOnError();
            break;
        case NetworkStates::SCANNING:
            m_scanDone = transitionByCondition(m_scanDone, NetworkStates::UP);
            m_connecting = transitionByCondition(m_connecting, NetworkStates::CONNECTED);
            transitionOnDisabled();
            transitionOnError();
            break;
        case NetworkStates::CONNECTED:
            transitionByCondition(!m_networkInfo.IsConnected, NetworkStates::UP);
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
            sendNetworkStatus();
            break;
        case NetworkStates::UP:
            m_networkDriver.up(DEFAULT_INTERFACE_NAME)
                .onError(m_errorCallback)
                .onSuccess(m_sendStatusCallback);
            break;
        case NetworkStates::SCANNING:
            m_networkDriver.triggerScan()
                .onError(m_errorCallback)
                .onSuccess(m_sendStatusCallback);
            break;
        case NetworkStates::CONNECTED:
            m_networkDriver.connectTo(m_networkInfo.Ssid)
                .onError(m_errorCallback)
                .onSuccess(m_sendStatusCallback);
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
        case NetworkStates::ERROR:
            m_errorCode = 0; // Reset error code
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
    NetworkStatus status {};

    switch (currentState()) {
        case NetworkStates::DOWN:
            status = NetworkStatus::DOWN;
            break;
        case NetworkStates::UP:
            status = NetworkStatus::UP;
            break;
        case NetworkStates::SCANNING:
            status = NetworkStatus::SEARCHING;
            break;
        case NetworkStates::CONNECTED:
            status = NetworkStatus::CONNECTED;
            break;
        case NetworkStates::ERROR:
            status = NetworkStatus::ERROR;
            break;
        default:
            status = NetworkStatus::ERROR;
            break;
    }

    NetworkStatusEvent event(status, m_networkInfo);
    m_mediator.notify(event);
}
