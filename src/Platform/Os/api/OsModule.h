#ifndef QLOCKY_OS_MODULE_H
#define QLOCKY_OS_MODULE_H

#include "api/ModuleBase.h"

/**
 * Os module contains functionality for operating system dependencies
 */
class OsModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    /**
     * @see ModuleBase::onInitialize
     */
    void onInitialize() final;

    OsModule() = default;
    ~OsModule() final = default;

private:
};

#endif