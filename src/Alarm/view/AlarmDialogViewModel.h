#ifndef ALARM_DIALOG_VIEW_MODEL_H
#define ALARM_DIALOG_VIEW_MODEL_H

#include <QDateTime>
#include <QObject>

#include "AlarmItemViewModel.h"
#include "internal/AlarmRepositoryIfc.h"
#include "SystemPreferencesRepositoryIfc.h"
#include "TimeConverter.h"

/**
 * ViewModel for the alarm dialog, handling alarm data loading and saving.
 */
class AlarmDialogViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(AlarmItemViewModel* item READ getItem CONSTANT)
    Q_PROPERTY(bool is24HourFormat READ is24HourFormat NOTIFY timeFormatChanged)

public:

    /**
     * Constructor
     * @param alarmRepository Reference to the alarm repository interface.
     * @param preferences Reference to the system preferences, used for the time format.
     */
    AlarmDialogViewModel(AlarmRepositoryIfc& alarmRepository, SystemPreferencesRepositoryIfc& preferences);

    /**
     * Loads the alarm data for the given alarm ID.
     * @param alarmId The ID of the alarm to load.
     */
    Q_INVOKABLE void loadAlarm(uint32_t const alarmId);

    /**
     * Saves the current alarm item to the repository.
     * If the alarm ID is negative, a new alarm is created; otherwise, the existing
     * alarm is updated.
     */
    Q_INVOKABLE void save();

    /**
     * Returns the AlarmItemViewModel associated with this dialog.
     */
    AlarmItemViewModel* getItem() {
        return &m_item;
    }

    /**
     * @return True if the time picker shows 24 hours, false for 12 hours with AM/PM.
     */
    bool is24HourFormat() const {
        return m_preferences.isTimeFormat24Hour();
    }

signals:
    void timeFormatChanged();

private:

    AlarmRepositoryIfc& m_alarmRepository;
    SystemPreferencesRepositoryIfc& m_preferences;
    AlarmItemViewModel m_item;
};

#endif