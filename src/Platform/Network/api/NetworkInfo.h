#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#include <cstdint>
#include <string>

/**
 * NetworkInfo holds information about the current network state.
 */
struct NetworkInfo {
    std::string Ssid;
    int32_t SignalStrength;
    bool IsConnected;
};

#endif
