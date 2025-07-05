#ifndef QLOCKY_PREFERENCES_MODULE_H
#define QLOCKY_PREFERENCES_MODULE_H

#include "api/ModuleBase.h"

/**
 * Preference module contains functionality for options and peristency
 */
class PreferencesModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    PreferencesModule() = default;
    ~PreferencesModule() final = default;

protected:

    /**
     * @see ModuleBase::onInitialize
     */
    void onInitialize() final;

private:
};

#endif