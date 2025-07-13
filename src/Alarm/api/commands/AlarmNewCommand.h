#ifndef ALARM_NEW_COMMAND_H
#define ALARM_NEW_COMMAND_H

#include <QDebug>

#include "Command/CommandDispatcherIfc.h"
#include "Command/QmlCommandBase.h"

class AlarmNewCommand final : public QmlCommandBase {
public:

    AlarmNewCommand(CommandDispatcherIfc& dispatcher);

    void doExecute(CommandArgs const& data) final;

private:

    CommandDispatcherIfc& m_dispatcher;
};

#endif