#ifndef QLOCKY_APPSHELL_UIMODULE_H
#define QLOCKY_APPSHELL_UIMODULE_H

#include "api/ModuleBase.h"

/**
 * UiModule is responsible for registering UI related components
 */
class UiModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    UiModule() = default;
    ~UiModule() final = default;

protected:

    void onInitialize() final;
};

#endif