#ifndef DEVICE_INFO_PROVIDER_IFC_H
#define DEVICE_INFO_PROVIDER_IFC_H

#include <string>

/**
 * Interface for device information retrieval.
 * This interface provides methods to retrieve various device-related information.
 * It is designed to be implemented by platform-specific device information providers.
 */
class DeviceInfoProviderIfc {
public:

    virtual ~DeviceInfoProviderIfc() = default;

    /**
     * Initializes the device information provider.
     */
    virtual void initialize() = 0;

    /**
     * Returns the device model name.
     * @return A string representing the device model.
     */
    virtual std::string getModelName() const = 0;

    /**
     * Returns the device operating system version.
     * @return A string representing the kernel version.
     */
    virtual std::string getKernelVersion() const = 0;

    /**
     * Returns the kernel build date.
     * @return A string representing the kernel build date.
     */
    virtual std::string getKernelBuildDate() const = 0;

    /**
     * Returns the device name.
     * @return A string representing the device name.
     */
    virtual std::string getDeviceName() const = 0;

    /**
     * Returns the device serial number.
     * @return A string representing the device serial number.
     */
    virtual std::string getSerialNumber() const = 0;

    /**
     * Returns the hostname of the device.
     * @return A string representing the hostname of the device.
     */
    virtual std::string getHostname() const = 0;
};

#endif