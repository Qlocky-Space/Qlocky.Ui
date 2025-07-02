#ifndef CLOCK_CARD_VIEW_MODEL_H
#define CLOCK_CARD_VIEW_MODEL_H

#include <api/Mediator.h>
#include <QObject>
#include <QString>

#include "internal/PingCommand.h"
#include "QmlCommandBase.h"
#include "TimeChangedEvent.h"

class ClockCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QmlCommandBase const* pingCommand READ getPingCommand NOTIFY pingCommandChanged)
    Q_PROPERTY(QString date READ getDate NOTIFY dateChanged)
    Q_PROPERTY(QString time READ getTime NOTIFY timeChanged)

public:

    ClockCardViewModel(Mediator& mediator, PingCommand& pingCommand);

    QmlCommandBase const* getPingCommand() const {
        return &m_pingCommand;
    }

    QString getDate() const {
        return m_date;
    }

    QString getTime() const {
        return m_time;
    }

signals:
    void pingCommandChanged();
    void dateChanged();
    void timeChanged();

private:

    void onTimeChanged(TimeChangedEvent const& event);

    QmlCommandBase& m_pingCommand;
    QString m_date;
    QString m_time;
};

#endif