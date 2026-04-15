#include "SettingItemViewModel.h"

void SettingItemViewModel::setTitle(QString const& title) {
    if (m_title != title) {
        m_title = title;
        emit titleChanged();
    }
}

void SettingItemViewModel::setCategory(QString const& category) {
    if (m_category != category) {
        m_category = category;
        emit categoryChanged();
    }
}

void SettingItemViewModel::setPath(QString const& path) {
    if (m_path != path) {
        m_path = path;
        emit pathChanged();
    }
}