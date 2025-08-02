#ifndef SETTING_LIST_MODEL_H
#define SETTING_LIST_MODEL_H

#include <QAbstractListModel>
#include <QString>

#include "SettingItemViewModel.h"

/**
 * ViewModel for a list of settings.
 */
class SettingListModel : public QAbstractListModel {
    Q_OBJECT

public:

    enum SettingRoles {
        TitleRole = Qt::UserRole + 1,
        CategoryRole,
        PathRole,
    };

    explicit SettingListModel();
    ~SettingListModel() final;

    /**
     * Returns the number of alarms in the list.
     * @param parent The parent index.
     * @return The number of alarms.
     */
    int rowCount(QModelIndex const& parent = QModelIndex()) const override;

    /**
     * Returns the data for a given index and role.
     * @param index The model index.
     * @param role The data role.
     * @return The requested data.
     */
    QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;

    /**
     * Returns the role names used by the model.
     * @return The role names.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * Adds an alarm to the model.
     * @param item The setting item to add.
     */
    void addItem(SettingItemViewModel* item);

private:

    QVector<SettingItemViewModel*> m_items;
};

#endif