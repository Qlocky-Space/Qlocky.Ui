#ifndef CONFIGURATION_REGISTRY_H
#define CONFIGURATION_REGISTRY_H

#include <unordered_map>

#include "ConfigurationRegistryIfc.h"
#include "view/SettingListModel.h"

class ConfigurationRegistry : public ConfigurationRegistryIfc {
public:

    ConfigurationRegistry(SettingListModel& model);

    /**
     * @see ConfigurationRegistryIfc::registerProvider
     */
    void registerProvider(std::string const& path, ConfigurationMeta const& meta) final;

    /**
     * @see ConfigurationRegistryIfc::meta
     */
    ConfigurationMeta const& meta(std::string const& path) const final;

private:

    SettingItemViewModel* createViewModel(std::string const& path, ConfigurationMeta const& meta);

    SettingListModel& m_model;
    std::unordered_map<std::string, ConfigurationMeta> m_map;
};

#endif // CONFIGURATION_REGISTRY_H
