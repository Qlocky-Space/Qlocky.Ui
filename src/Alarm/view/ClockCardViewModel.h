#ifndef CLOCK_CARD_VIEW_MODEL_H
#define CLOCK_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QDateTime>
#include <QObject>
#include <QString>

#include "internal/PingCommand.h"
#include "PreferencesServiceIfc.h"
#include "QmlCommandBase.h"
#include "TimeChangedEvent.h"

/**
 * View model for the clock card.
 */
class ClockCardViewModel : public QObject {
    Q_OBJECT

    // TODO remove demo
    Q_PROPERTY(QmlCommandBase const* pingCommand READ getPingCommand NOTIFY pingCommandChanged)

    Q_PROPERTY(QString date READ getDate NOTIFY dateChanged)
    Q_PROPERTY(QString time READ getTime NOTIFY timeChanged)

public:

    ClockCardViewModel(Mediator& mediator, PingCommand& pingCommand, PreferencesServiceIfc& preferences);

    // TODO remove demo
    QmlCommandBase const* getPingCommand() const {
        return &m_pingCommand;
    }

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
    void pingCommandChanged();
    void dateChanged();
    void timeChanged();

private:

    void onTimeChanged(TimeChangedEvent const& event);
    QDateTime getLocalTime(DateTime const timestamp);
    QString formatTime(QDateTime const& time);
    QString formatDate(QDateTime const& time);

    QmlCommandBase& m_pingCommand;
    QString m_date;
    QString m_time;
    PreferencesServiceIfc& m_preferences;
};

#endif