#ifndef QLOCKY_NETWORK_STATUS_EVENT_H
#define QLOCKY_NETWORK_STATUS_EVENT_H

#include <EventIfc.h>
#include <string>

#include "NetworkInfo.h"

enum class NetworkStatus : uint8_t {
    UP,
    DOWN,
    CONNECTED,
    SEARCHING,
    ERROR
};

/**
 * Network status event class
 */
class NetworkStatusEvent final : public EventIfc {
public:

    NetworkStatusEvent() = default;
    ~NetworkStatusEvent() final = default;

    /**
     * Constructor for NetworkStatusEvent.
     * @param status The current network status.
     * @param ssid The SSID of the connected network, if any.
     * @param airplaneMode Indicates if airplane mode is enabled.
     * @param signalStrength The signal strength of the connected network.
     */
    NetworkStatusEvent(NetworkStatus status, NetworkInfo const& networkInfo) :
        m_status(status),
        m_networkInfo(networkInfo) {
    }

    /**
     * Returns the strength of the network connection.
     * @return The network strength as an integer, -1 means no network.
     */
    int32_t networkStrength() const {
        if (m_status != NetworkStatus::CONNECTED) {
            return -1;
        }

        return m_networkInfo.SignalStrength;
    }

    /**
     * Returns the SSID of the connected network.
     * @return The SSID as a string.
     */
    std::string ssid() const {
        if (m_status != NetworkStatus::CONNECTED) {
            return "";
        }

        return m_networkInfo.Ssid;
    }

    /**
     * Returns the current network state.
     * @return The current network state as a NetworkStatus enum.
     */
    NetworkStatus networkState() const {
        return m_status;
    }

private:

    NetworkStatus m_status;
    NetworkInfo m_networkInfo;
};

#endif
