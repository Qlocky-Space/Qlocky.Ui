#ifndef CONFIGURATION_REGISTRY_H
#define CONFIGURATION_REGISTRY_H

#include <vector>

#include "ConfigurationProviderIfc.h"
#include "ConfigurationRegistryIfc.h"

class ConfigurationRegistry : public ConfigurationRegistryIfc {
public:

    void registerProvider(ConfigurationProviderIfc& provider) final;

private:

    std::vector<ConfigurationProviderIfc*> m_providers;
};

#endif // CONFIGURATION_REGISTRY_H
