#ifndef ALARM_LIST_ITEM_VIEW_MODEL_H
#define ALARM_LIST_ITEM_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QString>

/**
 * Model for the alarm.
 */
class AlarmItemViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int id READ getId)
    Q_PROPERTY(QString label READ getLabel WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(bool active READ getActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QDateTime time READ getTime WRITE setTime NOTIFY timeChanged)

public:

    AlarmItemViewModel(int const id);

    /**
     * Gets a unique alarm identifier
     */
    int getId() const {
        return m_id;
    }

    /**
     * Returns the label.
     * @return The label as a string.
     */
    QString getLabel() const {
        return m_label;
    }

    /**
     * Sets the label.
     * @param label The new label to set.
     */
    void setLabel(QString const& label);

    /**
     * Sets whether the object is active.
     * @param active True to activate, false to deactivate.
     */
    void setActive(bool active);

    /**
     * Returns whether the object is active.
     * @return True if active, false otherwise.
     */
    bool getActive() const {
        return m_active;
    }

    /**
     * Returns the formatted time string.
     * @return The current time as a string.
     */
    QDateTime getTime() const {
        return m_time;
    }

    /**
     * Sets the time.
     * @param time The time to set.
     */
    void setTime(QDateTime const& time);

signals:
    void labelChanged();
    void timeChanged();
    void activeChanged();
    void changed(AlarmItemViewModel const* alarm);

private:

    int m_id;
    QDateTime m_time;
    bool m_active;
    QString m_label;
};

#endif