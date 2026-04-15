#include "SettingListProxyModel.h"

#include "SettingItemViewModel.h"

SettingListProxyModel::SettingListProxyModel(SettingListModel& model) :
    QSortFilterProxyModel(nullptr) {
    setDynamicSortFilter(true);
    setSourceModel(&model);

    // Ensure category is always grouped together
    setSortRole(SettingListModel::SettingRoles::CategoryRole);
    sort(0, Qt::AscendingOrder);
}
