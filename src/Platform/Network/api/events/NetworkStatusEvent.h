#ifndef QLOCKY_NETWORK_STATUS_EVENT_H
#define QLOCKY_NETWORK_STATUS_EVENT_H

#include <EventIfc.h>
#include <string>

/**
 * Network status event class
 */
class NetworkStatusEvent final : public EventIfc {
public:

    NetworkStatusEvent() = default;
    ~NetworkStatusEvent() final = default;

    /**
     * Constructs a network status event with the given parameters.
     *
     * @param ssid The SSID of the connected network.
     * @param airplaneMode Whether the airplane mode is enabled.
     * @param networkStrength The strength of the network connection, -1 means no network.
     */
    NetworkStatusEvent(std::string ssid, bool const airplaneMode, int32_t const networkStrength) :
        m_ssid(std::move(ssid)), m_airplaneMode(airplaneMode), m_networkStrength(networkStrength) {
    }

    /**
     * Returns the SSID of the connected network.
     * @return The SSID as a string.
     */
    std::string ssid() const {
        return m_ssid;
    }

    /**
     * Returns whether the airplane mode is enabled.
     * @return True if airplane mode is enabled, false otherwise.
     */
    bool airplaneMode() const {
        return m_airplaneMode;
    }

    /**
     * Returns the strength of the network connection.
     * @return The network strength as an integer, -1 means no network.
     */
    int32_t networkStrength() const {
        return m_networkStrength;
    }

private:

    bool m_airplaneMode {false};
    int32_t m_networkStrength {-1};
    std::string m_ssid {};
};

#endif
