#ifndef ALARM_VIEW_ALARMLISTMODEL_H
#define ALARM_VIEW_ALARMLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "AlarmItemViewModel.h"

/**
 * List model for alarm items.
 *
 * Provides a Qt model interface for a list of AlarmItemViewModel objects.
 * Designed for use in QML and Qt views.
 */
class AlarmListModel : public QAbstractListModel {
    Q_OBJECT

public:

    enum AlarmRoles {
        AlarmRole = Qt::UserRole + 1
    };

    explicit AlarmListModel(QObject* parent = nullptr);

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
     * @param alarm The alarm to add.
     */
    void addAlarm(AlarmItemViewModel* alarm);

    /**
     * Removes an alarm from the model.
     * @param alarm The alarm to remove.
     */
    void removeAlarm(AlarmItemViewModel* alarm);

    /**
     * Returns the alarm at the given index.
     * @param id The unique identifier of the alarm.
     * @return The alarm item.
     */
    AlarmItemViewModel* alarmById(int id) const;

private:

    QVector<AlarmItemViewModel*> m_alarms;
};

#endif