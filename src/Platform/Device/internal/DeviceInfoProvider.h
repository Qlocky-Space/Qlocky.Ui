#ifndef DEVICE_INFO_PROVIDER_H
#define DEVICE_INFO_PROVIDER_H

#include "DeviceInfoProviderIfc.h"

/**
 * DeviceInfoProvider provides information about the device.
 */
class DeviceInfoProvider final : public DeviceInfoProviderIfc {
public:

    DeviceInfoProvider() = default;
    ~DeviceInfoProvider() final = default;

    /**
     * @see DeviceInfoProviderIfc::initialize
     */
    void initialize() final;

    /**
     * @see DeviceInfoProviderIfc::getModelName
     */
    std::string getModelName() const final {
        return m_modelName;
    }

    /**
     * @see DeviceInfoProviderIfc::getKernelVersion
     */
    std::string getKernelVersion() const final {
        return m_kernelVersion;
    }

    /**
     * @see DeviceInfoProviderIfc::getKernelBuildDate
     */
    std::string getKernelBuildDate() const final {
        return m_kernelBuildDate;
    }

    /**
     * @see DeviceInfoProviderIfc::getDeviceName
     */
    std::string getDeviceName() const final {
        return m_deviceName;
    }

    /**
     * @see DeviceInfoProviderIfc::getSerialNumber
     */
    std::string getSerialNumber() const final {
        return m_serialNumber;
    }

    /**
     * @see DeviceInfoProviderIfc::getHostname
     */
    std::string getHostname() const final {
        return m_hostname;
    }

private:

    std::string m_modelName {"QL-A100"};
    std::string m_deviceName {"MyDevice"};
    std::string m_serialNumber {"1234567890"};
    std::string m_kernelVersion;
    std::string m_kernelBuildDate;
    std::string m_hostname;
};

#endif