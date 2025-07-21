#ifndef ALARM_ACTIVE_DIALOG_VIEW_MODEL_H
#define ALARM_ACTIVE_DIALOG_VIEW_MODEL_H

#include <QDateTime>
#include <QObject>

#include "AlarmItemViewModel.h"
#include "internal/AlarmRepositoryIfc.h"
#include "TimeConverter.h"

/**
 * ViewModel for the active alarm dialog
 */
class AlarmActiveDialogViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(AlarmItemViewModel* item READ getItem CONSTANT)

public:

    /**
     * Constructor
     * @param alarmRepository Reference to the alarm repository interface.
     */
    AlarmActiveDialogViewModel(AlarmRepositoryIfc& alarmRepository);

    /**
     * Loads the alarm data for the given alarm ID.
     * @param alarmId The ID of the alarm to load.
     */
    Q_INVOKABLE void loadAlarm(uint32_t const alarmId);

    /**
     * Snoozes the alarm for a predefined duration.
     */
    Q_INVOKABLE void snooze();

    /**
     * Dismisses the alarm, removing it from the active state.
     */
    Q_INVOKABLE void dismiss();

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