#include "SettingPageViewModel.h"

#include <ng-log/logging.h>

SettingPageViewModel::SettingPageViewModel(ConfigurationRegistryIfc& registry, SettingListProxyModel& model) :
    QObject {nullptr},
    m_registry {registry},
    m_settingsModel {&model},
    m_selectedIndex {UINT32_MAX},
    m_currentPageTitle {""},
    m_currentPageComponent {""} {
}

void SettingPageViewModel::setSelectedIndex(uint32_t index) {
    if (m_selectedIndex != index) {
        m_selectedIndex = index;

        emit selectedIndexChanged();
        loadContent(index);
    }
}

void SettingPageViewModel::loadContent(uint32_t const index) {
    std::string path {getMetaPath(index)};
    ConfigurationMeta const meta {m_registry.meta(path)};

    if (meta.qmlPath.empty()) {
        LOG(WARNING) << "No configuration path available.";
        return;
    }

    if (meta.qmlPath == m_currentPageComponent.toStdString()) {
        return;
    }

    m_currentPageComponent = QString::fromStdString(meta.qmlPath);
    m_currentPageTitle = QString::fromStdString(meta.title);
    emit currentPageTitleChanged();
    emit currentPageComponentChanged();
}

std::string SettingPageViewModel::getMetaPath(uint32_t const index) const {
    QModelIndex const modelIndex = m_settingsModel->index(index, 0);
    if (!modelIndex.isValid()) {
        return "";
    }

    auto path {m_settingsModel->data(modelIndex, SettingListModel::SettingRoles::PathRole).toString()};
    if (path.isEmpty()) {
        return "";
    }

    return path.toStdString();
}
