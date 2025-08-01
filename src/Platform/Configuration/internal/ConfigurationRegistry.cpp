#include "ConfigurationRegistry.h"

void ConfigurationRegistry::registerProvider(ConfigurationProviderIfc& provider) {
    m_providers.push_back(&provider);
}
