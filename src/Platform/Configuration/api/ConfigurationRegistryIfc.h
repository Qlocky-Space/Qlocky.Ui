#ifndef CONFIGURATION_REGISTRY_IFC_H
#define CONFIGURATION_REGISTRY_IFC_H

#include "ConfigurationProviderIfc.h"

/**
 * Interface for configuration registry.
 */
class ConfigurationRegistryIfc {
public:

    virtual ~ConfigurationRegistryIfc() = default;

    /**
     * Register a configuration provider.
     * @param provider The configuration provider to register.
     */
    virtual void registerProvider(ConfigurationProviderIfc& provider) = 0;
};

#endif // CONFIGURATION_REGISTRY_IFC_H