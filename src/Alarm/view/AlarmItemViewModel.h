#ifndef ALARM_LIST_ITEM_VIEW_MODEL_H
#define ALARM_LIST_ITEM_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QString>

/**
 * ViewModel representing a single alarm item.
 *
 * Exposes properties like ID, label, enabled state, and scheduled time
 * for use in QML or UI binding contexts.
 */
class AlarmItemViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int alarmId READ getAlarmId CONSTANT)
    Q_PROPERTY(QString displayName READ getDisplayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(bool state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QDateTime dueTime READ getDueTime WRITE setDueTime NOTIFY dueTimeChanged)

public:

    /**
     * Constructs an AlarmItemViewModel with a given alarm ID.
     * @param id Unique identifier for this alarm.
     */
    explicit AlarmItemViewModel(int const id);

    /**
     * Gets the unique alarm identifier.
     * @return The alarm ID.
     */
    int getAlarmId() const {
        return m_id;
    }

    /**
     * Gets the display name of the alarm.
     * @return The display name.
     */
    QString getDisplayName() const {
        return m_displayName;
    }

    /**
     * Sets the display name of the alarm.
     * @param displayName The new display name to set.
     */
    void setDisplayName(QString const& displayName);

    /**
     * Sets the active state of the alarm.
     * @param state True to enable the alarm, false to disable.
     */
    void setState(bool state);

    /**
     * Gets the active state of the alarm.
     * @return True if the alarm is enabled, false otherwise.
     */
    bool getState() const {
        return m_state;
    }

    /**
     * Gets the scheduled time for the alarm.
     * @return The due time as a QDateTime.
     */
    QDateTime getDueTime() const {
        return m_dueTime;
    }

    /**
     * Sets the scheduled time for the alarm.
     * @param dueTime The new due time to set.
     */
    void setDueTime(QDateTime const& dueTime);

    /**
     * Updates this view model from another instance.
     * @param other The source view model to copy data from.
     */
    void updateFrom(AlarmItemViewModel const& other);

signals:
    void displayNameChanged();
    void dueTimeChanged();
    void stateChanged();

private:

    int m_id;
    QDateTime m_dueTime;
    bool m_state;
    QString m_displayName;
};

#endif
