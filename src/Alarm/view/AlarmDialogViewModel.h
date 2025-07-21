#ifndef ALARM_DIALOG_VIEW_MODEL_H
#define ALARM_DIALOG_VIEW_MODEL_H

#include <QDateTime>
#include <QObject>

#include "AlarmItemViewModel.h"
#include "internal/AlarmRepositoryIfc.h"
#include "TimeConverter.h"

/**
 * ViewModel for the alarm dialog, handling alarm data loading and saving.
 */
class AlarmDialogViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(AlarmItemViewModel* item READ getItem CONSTANT)

public:

    /**
     * Constructor
     * @param alarmRepository Reference to the alarm repository interface.
     */
    AlarmDialogViewModel(AlarmRepositoryIfc& alarmRepository);

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

private:

    AlarmRepositoryIfc& m_alarmRepository;
    AlarmItemViewModel m_item;
};

#endif