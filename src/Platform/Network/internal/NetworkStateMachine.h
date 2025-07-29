#ifndef NETWORK_STATE_MACHINE_H
#define NETWORK_STATE_MACHINE_H

#include <cstdint>
#include <functional>
#include <Mediator.h>
#include <NetworkDriverIfc.h>
#include <StateMachineBase.h>
#include <string>

#include "NetworkDriverErrorCode.h"
#include "NetworkProfile.h"
#include "NetworkProfileEntity.h"

/**
 * NetworkStateMachine is a state machine for managing network states.
 * @see https://www.notion.so/qlocky/Software-Detail-Qlocky-UI-19b2f01a2805805b9bfcda8a7044615c?source=copy_link#23d2f01a280580c4b1d2e5eaa8c4e963
 */
enum class NetworkStates {
    INITIAL,

    DOWN = INITIAL,
    UP,
    CONNECTING,
    CONNECTED,
    ERROR
};

/**
 * NetworkStateMachine is a concrete implementation of StateMachineBase for managing network states.
 */
class NetworkStateMachine : public StateMachineBase<NetworkStates>, public NetworkDriverListenerIfc {
public:

    NetworkStateMachine(Mediator& mediator, NetworkDriverIfc& networkDriver) :
        m_mediator {mediator},
        m_networkDriver {networkDriver} {
    }

    ~NetworkStateMachine() = default;

    /**
     * Forces the state machine to process all events.
     * This method is used to ensure that all events are processed immediately,
     */
    void forceEvents();

    /**
     * Transition to the DOWN state.
     * This method is called when the network interface is brought down.
     */
    void disable();

    /**
     * Transition to the SCANNING state.
     * This method is called when the network interface is brought up.
     */
    void enable();

    /**
     * Start a network connection to the specified profile.
     * @param profile The network profile to connect to.
     */
    void connectTo(NetworkProfileEntity const& profile);

    /**
     * Disconnect from the current network.
     */
    void disconnect();

    /**
     * Transition to the ERROR state.
     * This method is called when an error occurs in the network state machine.
     * @param errorCode The error code associated with the error.
     */
    void onError(int32_t errorCode);

    /**
     * @see NetworkDriverListenerIfc::onInterfaceStatusChanged
     */
    void onInterfaceStatusChanged(NetworkIfStatus const status) final;

    /**
     * @see NetworkDriverListenerIfc::onScanCompleted
     */
    void onScanCompleted(bool success) final;

    /**
     * @see NetworkDriverListenerIfc::onScanResultsAvailable
     */
    void onScanResultsAvailable(ScanResult& result) final;

protected:

    void onTransition(NetworkStates const state) final;
    void onEnterState(NetworkStates const state) final;
    void onLeaveState(NetworkStates const state) final;
    void onRunState(NetworkStates const state) final;

    void transitionOnError();
    void transitionOnDisabled();

    void setErrorCode(NetworkDriverErrorCode const errorCode) {
        m_errorCode = static_cast<int32_t>(errorCode);
        runStateMachine();
    }

    void sendNetworkStatus();
    void sendConnectionStatus();

    void clearFlags() override {
        m_connected = false;
        m_connecting = false;
        m_disconnect = false;
        m_scanDone = false;
        m_lost = false;
        m_disabled = false;
        m_enabled = false;
    }

private:

    using NetworkErrorCallback = std::function<void(NetworkDriverErrorCode const&)>;
    using NetworkCallback = std::function<void(bool)>;

    // On BSP only one network interface is supported.
    inline static std::string const DEFAULT_INTERFACE_NAME = "wlan0";

    // Data
    Mediator& m_mediator;
    NetworkDriverIfc& m_networkDriver;
    NetworkErrorCallback m_errorCallback {[this](NetworkDriverErrorCode const& errorCode) {
        setErrorCode(errorCode);
    }};
    NetworkCallback m_sendStatusCallback {[this](bool) {
        sendNetworkStatus();
    }};

    int32_t m_errorCode {0};
    NetworkProfile m_activeProfile {};

    // Flags
    bool m_connected {false};
    bool m_connecting {false};
    bool m_disconnect {false};
    bool m_lost {false};
    bool m_scanDone {false};
    bool m_disabled {false};
    bool m_enabled {false};
};

#endif