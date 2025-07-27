#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#include <cstdint>
#include <string>

/**
 * NetworkInfo holds information about the current network state.
 */
struct NetworkInfo {
public:

    NetworkInfo(std::string ssid, int32_t signalStrength, bool isConnected) :
        m_ssid(std::move(ssid)),
        m_signalStrength(signalStrength),
        m_isConnected(isConnected) {
    }

    NetworkInfo() = default;

    /**
     * Get the SSID of the connected network.
     * @return SSID as a string.
     */
    std::string getSsid() const {
        return m_ssid;
    }

    /**
     * Get the signal strength of the network.
     * @return Signal strength in dBm.
     */
    int32_t getSignalStrength() const {
        return m_signalStrength;
    }

    /**
     * Check if the device is connected to a network.
     * @return True if connected, false otherwise.
     */
    bool isConnected() const {
        return m_isConnected;
    }

private:

    std::string m_ssid;
    int32_t m_signalStrength;
    bool m_isConnected;
};

#endif
