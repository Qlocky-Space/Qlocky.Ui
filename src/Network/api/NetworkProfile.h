#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#include <cstdint>
#include <string>

/**
 * NetworkProfile holds information about the current network state.
 */
struct NetworkProfile {
    uint32_t Id; // Unique identifier for the network profile

    std::string Ssid;
    int32_t SignalStrength;
    bool IsConnected;
};

#endif
