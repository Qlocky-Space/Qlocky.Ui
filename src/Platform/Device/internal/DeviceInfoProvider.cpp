#include "DeviceInfoProvider.h"

#include <sys/utsname.h>

std::string DeviceInfoProvider::getModelName() const {
    return "QL-A100";
}

std::string DeviceInfoProvider::getKernelVersion() const {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        return "Unknown";
    }

    return std::string(buffer.release);
}

std::string DeviceInfoProvider::getKernelBuildDate() const {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        return "Unknown";
    }

    return std::string(buffer.version);
}

std::string DeviceInfoProvider::getDeviceName() const {
    return "MyDevice";
}

std::string DeviceInfoProvider::getSerialNumber() const {
    return "1234567890";
}
