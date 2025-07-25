#ifndef QLOCKY_NETWORK_MODULE_H
#define QLOCKY_NETWORK_MODULE_H

#include "api/ModuleBase.h"

/**
 * Network module contains functionality for network-related operations
 */
class NetworkModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    NetworkModule() = default;
    ~NetworkModule() final = default;

private:
};

#endif