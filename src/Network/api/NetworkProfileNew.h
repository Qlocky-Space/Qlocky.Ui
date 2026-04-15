#ifndef NETWORK_PROFILE_NEW_H
#define NETWORK_PROFILE_NEW_H

#include <cstdint>
#include <string>

/**
 * NetworkProfileNew holds information about a new network.
 */
struct NetworkProfileNew {
    std::string Ssid;
    std::string Psk;
    std::string SecurityType {"WPA-PSK"};
    bool AutoConnect {false};
};

#endif
