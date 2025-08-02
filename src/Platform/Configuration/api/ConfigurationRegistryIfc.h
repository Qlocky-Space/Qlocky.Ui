#ifndef CONFIGURATION_REGISTRY_IFC_H
#define CONFIGURATION_REGISTRY_IFC_H

#include <string>

struct ConfigurationMeta {
    /**
     * Category of the configuration item.
     */
    std::string category;

    /**
     * Title of the configuration item.
     */
    std::string title;

    /**
     * Path to the QML file associated with the configuration item.
     */
    std::string qmlPath;

    ConfigurationMeta(std::string const& category, std::string const& title, std::string const& qmlPath) :
        category {category},
        title {title},
        qmlPath {qmlPath} {
    }
    ConfigurationMeta() = default;
};

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
    virtual void registerProvider(std::string const& path, ConfigurationMeta const& meta) = 0;

    /**
     * Retrieves the metadata for a given configuration path.
     * @param path The configuration path to look up.
     * @return Reference to the associated metadata.
     */
    virtual ConfigurationMeta const& meta(std::string const& path) const = 0;
};

#endif // CONFIGURATION_REGISTRY_IFC_H