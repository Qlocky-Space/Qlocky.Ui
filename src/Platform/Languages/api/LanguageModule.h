#ifndef QLOCKY_LANGUAGE_MODULE_H
#define QLOCKY_LANGUAGE_MODULE_H

#include "api/ModuleBase.h"

/**
 * Language module contains functionality for
 */
class LanguageModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    LanguageModule() = default;
    ~LanguageModule() final = default;

protected:

    /**
     * @see ModuleBase::onInitialize
     */
    void onInitialize() final;

private:
};

#endif