#include "DeviceInfoProvider.h"

#include <fstream>
#include <ng-log/logging.h>
#include <sys/utsname.h>
#include <unistd.h>

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