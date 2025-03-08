#ifndef QLOCKY_APPSHELL_APPSHELLMODULE_H
#define QLOCKY_APPSHELL_APPSHELLMODULE_H

#include "api/ModuleBase.h"

/**
 * AppShell module contains functionality for
 */
class AppShellModule : public ModuleBase {
public:

    void registerExports(Injector& container) final;

    void registerQmlTypes() final;
};

#endif