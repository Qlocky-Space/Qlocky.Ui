#ifndef QLOCKY_DEVICE_MODULE_H
#define QLOCKY_DEVICE_MODULE_H

#include "api/ModuleBase.h"

/**
 * Device module contains functionality for operating device dependencies
 */
class DeviceModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    DeviceModule() = default;
    ~DeviceModule() final = default;

private:
};

#endif