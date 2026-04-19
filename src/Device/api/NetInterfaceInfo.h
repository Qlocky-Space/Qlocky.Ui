#ifndef NET_INTERFACE_INFO_H
#define NET_INTERFACE_INFO_H

#include <cstdint>
#include <string>

/**
 * NetInterfaceInfo holds information about a network interface.
 */
struct NetInterfaceInfo {
    std::string Name;
    std::string MacAddress;
    std::vector<std::string> IpAddresses; // supports IPv4 + IPv6
    bool IsUp;
};

#endif
