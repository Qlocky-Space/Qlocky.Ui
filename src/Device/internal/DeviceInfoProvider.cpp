#include "DeviceInfoProvider.h"

#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <ifaddrs.h>
#include <iomanip>
#include <map>
#include <net/if.h>
#include <netdb.h>
#include <netpacket/packet.h>
#include <ng-log/logging.h>
#include <sstream>
#include <sys/ioctl.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <vector>

void DeviceInfoProvider::initialize() {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        m_kernelVersion = "Unknown";
        m_kernelBuildDate = "Unknown";
        m_hostname = "Unknown";

        LOG(WARNING) << "Failed to retrieve system information: " << strerror(errno);
    }
    else {
        m_kernelVersion = std::string(buffer.release);
        m_kernelBuildDate = std::string(buffer.version);
        m_hostname = std::string(buffer.nodename);
    }
}

void DeviceInfoProvider::setHostname(std::string const& hostname) {
    if (hostname.empty()) {
        return;
    }
    if (hostname == m_hostname) {
        return; // No change
    }

    if (sethostname(hostname.c_str(), hostname.size()) != 0) {
        LOG(WARNING) << "Failed to set hostname: " << strerror(errno);
        return;
    }

    // Persist the hostname to /etc/hostname
    std::ofstream file {"/etc/hostname"};
    if (!file) {
        LOG(WARNING) << "Failed to open /etc/hostname for writing: " << strerror(errno);
        return;
    }
    file << hostname << std::endl;
    if (!file) {
        LOG(WARNING) << "Failed to write hostname to /etc/hostname";
        return;
    }

    m_hostname = hostname;
}

std::vector<NetInterfaceInfo> DeviceInfoProvider::getNetInterfaceInfos() const {
    std::map<std::string, NetInterfaceInfo> interfacesMap {};

    struct ifaddrs* ifaddr = nullptr;
    if (getifaddrs(&ifaddr) == -1) {
        LOG(WARNING) << "getifaddrs failed: " << strerror(errno);
        return {};
    }

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        LOG(WARNING) << "socket failed: " << strerror(errno);
        freeifaddrs(ifaddr);
        return {};
    }

    for (struct ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (!ifa->ifa_name) {
            continue;
        }

        std::string name = ifa->ifa_name;
        auto& iface = interfacesMap[name];
        iface.Name = name;
        iface.IsUp = (ifa->ifa_flags & IFF_UP) != 0;

        if (!ifa->ifa_addr) {
            continue;
        }

        char host[NI_MAXHOST];

        // IPv4
        if (ifa->ifa_addr->sa_family == AF_INET) {
            auto* sa = reinterpret_cast<struct sockaddr_in*>(ifa->ifa_addr);
            if (inet_ntop(AF_INET, &(sa->sin_addr), host, NI_MAXHOST)) {
                iface.IpAddresses.emplace_back(host);
            }
        }

        // Get MAC address once per interface
        if (iface.MacAddress.empty()) {
            struct ifreq ifr {};
            std::strncpy(ifr.ifr_name, name.c_str(), IFNAMSIZ - 1);

            if (ioctl(fd, SIOCGIFHWADDR, &ifr) == 0) {
                unsigned char* mac = reinterpret_cast<unsigned char*>(ifr.ifr_hwaddr.sa_data);

                std::ostringstream macStream;
                macStream << std::hex << std::setfill('0');

                for (int i = 0; i < 6; ++i) {
                    macStream << std::setw(2) << static_cast<int>(mac[i]);
                    if (i != 5) {
                        macStream << ":";
                    }
                }

                iface.MacAddress = macStream.str();
            }
        }
    }

    close(fd);
    freeifaddrs(ifaddr);

    // aggregate interfaces by name
    std::vector<NetInterfaceInfo> netInterfaceInfos {};
    for (auto& [_, iface] : interfacesMap) {
        netInterfaceInfos.push_back(std::move(iface));
    }

    return netInterfaceInfos;
}
