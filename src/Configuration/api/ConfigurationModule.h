#ifndef CONFIGURATION_MODULE_H
#define CONFIGURATION_MODULE_H

#include <ModuleBase.h>

/**
 * ConfigurationModule is responsible for managing application configuration.
 */
class ConfigurationModule : public ModuleBase {
public:

    ConfigurationModule() = default;
    ~ConfigurationModule() final = default;

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    /**
     * @see ModuleBase::registerExports
     */
    void registerQmlTypes() final;

    /**
     * @see ModuleBase::onInitialize
     */
    void onInitialize() final;
};

#endif // CONFIGURATION_MODULE_H