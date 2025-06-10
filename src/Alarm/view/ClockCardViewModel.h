#ifndef CLOCK_CARD_VIEW_MODEL_H
#define CLOCK_CARD_VIEW_MODEL_H

#include <QObject>

#include "internal/PingCommand.h"
#include "QmlCommandBase.h"

class ClockCardViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QmlCommandBase const* pingCommand READ getPingCommand NOTIFY pingCommandChanged)

public:

    explicit ClockCardViewModel(PingCommand& pingCommand) :
        QObject {nullptr},
        m_pingCommand {pingCommand} {
    }

    QmlCommandBase const* getPingCommand() const {
        return &m_pingCommand;
    }

signals:
    void pingCommandChanged();

private:

    QmlCommandBase& m_pingCommand;
};

#endif