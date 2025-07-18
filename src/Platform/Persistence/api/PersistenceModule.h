#ifndef QLOCKY_PERSISTENCE_MODULE_H
#define QLOCKY_PERSISTENCE_MODULE_H

#include "api/ModuleBase.h"

/**
 * Preference module contains functionality for options and peristency
 */
class PersistenceModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    PersistenceModule() = default;
    ~PersistenceModule() final = default;

protected:

    /**
     * @see ModuleBase::onInitialize
     */
    void onInitialize() final;

private:
};

#endif