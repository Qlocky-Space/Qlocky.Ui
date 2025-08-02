#ifndef SETTING_LIST_PROXY_MODEL_H
#define SETTING_LIST_PROXY_MODEL_H

#include <QSortFilterProxyModel>

#include "SettingListModel.h"

/**
 * Proxy model for filtering and sorting settings in the SettingListModel.
 * This is required to sort by category to ensure only one category is shown at a time
 *
 * Further filtering and sorting can be implemented as needed.
 */
class SettingListProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:

    explicit SettingListProxyModel(SettingListModel& model);
    ~SettingListProxyModel() final = default;
};

#endif