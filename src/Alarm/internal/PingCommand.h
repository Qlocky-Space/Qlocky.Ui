#ifndef PING_COMMAND_H
#define PING_COMMAND_H

#include <QDebug>

#include "QmlCommandBase.h"

class PingCommand final : public QmlCommandBase {
public:

    void doExecute() override {
        // Implementation of the ping command logic
        // This could be a network ping, a system check, etc.
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