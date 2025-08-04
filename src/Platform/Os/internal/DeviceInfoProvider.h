#ifndef DEVICE_INFO_PROVIDER_H
#define DEVICE_INFO_PROVIDER_H

#include "DeviceInfoProviderIfc.h"

class DeviceInfoProvider final : public DeviceInfoProviderIfc {
public:

    DeviceInfoProvider() = default;
    ~DeviceInfoProvider() final = default;

    /**
     * @see DeviceInfoProviderIfc::getModel
     */
    std::string getModelName() const final;

    /**
     * @see DeviceInfoProviderIfc::getKernelVersion
     */
    std::string getKernelVersion() const final;

    /**
     * @see DeviceInfoProviderIfc::getKernelBuildDate
     */
    std::string getKernelBuildDate() const final;

    /**
     * @see DeviceInfoProviderIfc::getDeviceName
     */
    std::string getDeviceName() const final;

    /**
     * @see DeviceInfoProviderIfc::getSerialNumber
     */
    std::string getSerialNumber() const final;
};

#endif