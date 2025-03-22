#ifndef QLOCKY_RADIO_MODULE_H
#define QLOCKY_RADIO_MODULE_H

#include "api/ModuleBase.h"

/**
 * Radio module contains functionality for
 */
class RadioModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    RadioModule() = default;
    ~RadioModule() final = default;

private:
};

#endif