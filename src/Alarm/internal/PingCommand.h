#ifndef PING_COMMAND_H
#define PING_COMMAND_H

#include <QDebug>

#include "Command/QmlCommandBase.h"

// TODO remove this demo command
class PingCommand final : public QmlCommandBase {
public:

    void doExecute() override {
        qDebug() << "Ping command executed (" << m_pingCount << "/5)";
        m_pingCount++;

        if (m_pingCount >= 5) {
            setCanExecute(false);
        }
    }

private:

    uint32_t m_pingCount {0};
};

#endif