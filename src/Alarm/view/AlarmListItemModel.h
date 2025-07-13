#ifndef ALARM_LIST_ITEM_VIEW_MODEL_H
#define ALARM_LIST_ITEM_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QString>

/**
 * View model for the alarm list card.
 */
class AlarmListItemModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString label READ getLabel WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(bool active READ getActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QDateTime time READ getTime WRITE setTime NOTIFY timeChanged)

public:

    AlarmListItemModel();

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

private:

    QDateTime m_time;
    bool m_active;
    QString m_label;
};

#endif