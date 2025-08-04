#include "ConfigurationRegistry.h"

ConfigurationRegistry::ConfigurationRegistry(SettingListModel& model) :
    m_model {model},
    m_map {} {
}

void ConfigurationRegistry::registerProvider(std::string const& path, ConfigurationMeta const& meta) {
    if (m_map.count(path) > 0) {
        return;
    }

    m_model.addItem(createViewModel(path, meta));

    m_map[path] = meta;
}

ConfigurationMeta const& ConfigurationRegistry::meta(std::string const& path) const {
    return m_map.at(path);
}

SettingItemViewModel* ConfigurationRegistry::createViewModel(std::string const& path, ConfigurationMeta const& meta) {
    auto item = new SettingItemViewModel();
    item->setTitle(QString::fromStdString(meta.title));
    item->setCategory(QString::fromStdString(meta.category));
    item->setPath(QString::fromStdString(path));
    return item;
}
