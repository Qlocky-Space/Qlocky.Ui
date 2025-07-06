#ifndef QLOCKY_APPSHELL_APPSHELLMODULE_H
#define QLOCKY_APPSHELL_APPSHELLMODULE_H

#include "api/ModuleBase.h"

/**
 * AppShell module contains functionality for
 */
class AppShellModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    /**
     * @see ModuleBase::registerQmlTypes
     */
    void registerQmlTypes() final;

    AppShellModule() = default;
    ~AppShellModule() final = default;

protected:

    void onInitialize() final;
};

#endif