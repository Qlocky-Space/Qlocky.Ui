#ifndef PING_COMMAND_H
#define PING_COMMAND_H

#include <QDebug>

#include "QmlCommandBase.h"

// TODO remove this demo command
class PingCommand final : public QmlCommandBase {
public:

    void doExecute() override {
        qDebug() << "Ping command executed (" << m_pingCount << ")";
        m_pingCount++;

        if (m_pingCount >= 5) {
            setCanExecute(false);
        }
    }

private:

    uint32_t m_pingCount {0};
};

#endif