#include "DeviceInfoProvider.h"

#include <sys/utsname.h>

void DeviceInfoProvider::initialize() {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        m_kernelVersion = "Unknown";
        m_kernelBuildDate = "Unknown";
        m_hostname = "Unknown";
    }
    else {
        m_kernelVersion = std::string(buffer.release);
        m_kernelBuildDate = std::string(buffer.version);
        m_hostname = std::string(buffer.nodename);
    }
}
