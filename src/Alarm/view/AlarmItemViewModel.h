
#ifndef ALARM_LIST_ITEM_VIEW_MODEL_H
#define ALARM_LIST_ITEM_VIEW_MODEL_H

#include <api/Mediator.h>
#include <DayOfWeekViewModel.h>
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

    Q_PROPERTY(uint32_t alarmId READ getAlarmId CONSTANT)
    Q_PROPERTY(QString displayName READ getDisplayName WRITE setDisplayName NOTIFY displayNameChanged)
    Q_PROPERTY(bool state READ getState WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(uint32_t dueTime READ getDueTime WRITE setDueTime NOTIFY dueTimeChanged)
    Q_PROPERTY(uint32_t snoozeTime READ snoozeTime WRITE setSnoozeTime NOTIFY snoozeTimeChanged)
    Q_PROPERTY(uint8_t maxSnoozeCount READ getMaxSnoozeCount WRITE setMaxSnoozeCount NOTIFY maxSnoozeCountChanged)
    Q_PROPERTY(uint8_t snoozeCount READ getSnoozeCount WRITE setSnoozeCount NOTIFY snoozeCountChanged)
    Q_PROPERTY(DayOfWeekViewModel::Days daysOfWeek READ getDaysOfWeek WRITE setDaysOfWeek NOTIFY daysOfWeekChanged)

public:

    /**
     * Constructs an AlarmItemViewModel with a given alarm ID.
     * @param id Unique identifier for this alarm.
     */
    explicit AlarmItemViewModel(uint32_t const id);

    /**
     * Gets the unique alarm identifier.
     * @return The alarm ID.
     */
    uint32_t getAlarmId() const {
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
    uint32_t getDueTime() const {
        return m_dueTime;
    }

    /**
     * Sets the scheduled time for the alarm.
     * @param dueTime The new due time to set.
     */
    void setDueTime(uint32_t const dueTime);

    /**
     * Checks if the alarm is set to repeat.
     * @return True if the alarm is repeated, false otherwise.
     */
    bool isRepeated() const {
        return m_daysOfWeek != DayOfWeekViewModel::Day::None;
    }

    /**
     * Gets the snooze time in minutes.
     * @return The snooze time in minutes.
     */
    uint32_t snoozeTime() const {
        return m_snoozeTime;
    }

    /**
     * Sets the snooze time in minutes.
     * @param snoozeTime The new snooze time to set.
     */
    void setSnoozeTime(uint32_t snoozeTime);

    /**
     * Gets the maximum number of snoozes allowed.
     * @return The maximum snooze count.
     */
    uint8_t getMaxSnoozeCount() const {
        return m_maxSnoozeCount;
    }

    /**
     * Sets the maximum number of snoozes allowed.
     * @param maxSnoozeCount The new maximum snooze count to set.
     */
    void setMaxSnoozeCount(uint8_t maxSnoozeCount);

    /**
     * Gets the current snooze count.
     * @return The current snooze count.
     */
    uint8_t getSnoozeCount() const {
        return m_snoozeCount;
    }

    /**
     * Sets the current snooze count.
     * @param snoozeCount The new snooze count to set.
     */
    void setSnoozeCount(uint8_t snoozeCount);

    /**
     * Gets the days of the week when the alarm is active.
     * @return The days of the week as a DayOfWeek enum.
     */
    DayOfWeekViewModel::Days getDaysOfWeek() const {
        return m_daysOfWeek;
    }

    /**
     * Sets the days of the week when the alarm is active.
     * @param daysOfWeek The new days of the week to set.
     */
    void setDaysOfWeek(DayOfWeekViewModel::Days daysOfWeek);

    /**
     * Updates this view model from another instance.
     * @param other The source view model to copy data from.
     */
    void updateFrom(AlarmItemViewModel const& other);

signals:
    void displayNameChanged();
    void dueTimeChanged();
    void stateChanged();
    void snoozeTimeChanged();
    void maxSnoozeCountChanged();
    void snoozeCountChanged();
    void daysOfWeekChanged();

private:

    uint32_t m_id;
    uint32_t m_dueTime;
    bool m_state;
    QString m_displayName;
    uint32_t m_snoozeTime;
    uint8_t m_maxSnoozeCount;
    uint8_t m_snoozeCount;
    DayOfWeekViewModel::Days m_daysOfWeek;
};

#endif
