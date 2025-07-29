#ifndef OS_NETWORK_INFO_H
#define OS_NETWORK_INFO_H

#include <string>

struct NetworkInfo {
    std::string ssid;
    std::string psk;
    std::string keyMgmnt;
};

#endif