#ifndef ALARM_EDIT_COMMAND_H
#define ALARM_EDIT_COMMAND_H

#include <QDebug>

#include "Command/CommandDispatcherIfc.h"
#include "Command/QmlCommandBase.h"

class AlarmEditCommand final : public QmlCommandBase {
public:

    AlarmEditCommand(CommandDispatcherIfc& dispatcher);

    void doExecute(CommandArgs const& data) final;

private:

    CommandDispatcherIfc& m_dispatcher;
};

#endif