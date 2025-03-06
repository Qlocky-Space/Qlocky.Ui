#ifndef QLOCKY_APPSHELL_APPSHELLMODULE_H
#define QLOCKY_APPSHELL_APPSHELLMODULE_H

#include "api/ModuleIfc.h"

/**
 * AppShell module contains functionality for
 */
class AppShellModule : public ModuleIfc {
public:

    void registerExports(Injector& container) final;

    void registerQmlTypes() final;
};

#endif