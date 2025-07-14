#ifndef ALARM_DIALOG_VIEW_MODEL_H
#define ALARM_DIALOG_VIEW_MODEL_H

#include <QDateTime>
#include <QObject>

#include "internal/AlarmRepositoryIfc.h"

class AlarmDialogViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString displayName READ getDisplayName CONSTANT)
    Q_PROPERTY(bool state READ getState CONSTANT)
    Q_PROPERTY(QDateTime dueTime READ getDueTime CONSTANT)

public:

    /**
     * Constructor
     * @param alarmRepository Reference to the alarm repository interface.
     */
    AlarmDialogViewModel(AlarmRepositoryIfc& alarmRepository);

    /**
     * Gets the display name of the alarm.
     * @return The display name of the alarm.
     */
    QString getDisplayName() const {
        return m_displayName;
    }

    /**
     * Gets the alarm state.
     * @return True if the alarm is active, false otherwise.
     */
    bool getState() const {
        return m_state;
    }

    /**
     * Gets the due time of the alarm.
     * @return The due time of the alarm.
     */
    QDateTime getDueTime() const {
        return m_dueTime;
    }

    Q_INVOKABLE void save();

private:

    AlarmRepositoryIfc& m_alarmRepository;

    QString m_displayName;
    bool m_state;
    QDateTime m_dueTime;
};

#endif