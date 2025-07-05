#ifndef CLOCK_CARD_VIEW_MODEL_H
#define CLOCK_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QString>

#include "PreferencesServiceIfc.h"
#include "TimeChangedEvent.h"

/**
 * View model for the clock card.
 */
class ClockCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString date READ getDate NOTIFY dateChanged)
    Q_PROPERTY(QString time READ getTime NOTIFY timeChanged)

public:

    ClockCardViewModel(Mediator& mediator, PreferencesServiceIfc& preferences);

    /**
     * Returns the formatted date string.
     * @return The current date as a string.
     */
    QString getDate() const {
        return m_date;
    }

    /**
     * Returns the formatted time string.
     * @return The current time as a string.
     */
    QString getTime() const {
        return m_time;
    }

signals:
    void dateChanged();
    void timeChanged();

private:

    void onTimeChanged(TimeChangedEvent const& event);
    QDateTime getLocalTime(DateTime const timestamp);
    QString formatTime(QDateTime const& time);
    QString formatDate(QDateTime const& time);

    QString m_date;
    QString m_time;
    PreferencesServiceIfc& m_preferences;
};

#endif