#ifndef ALARM_REMOVE_COMMAND_H
#define ALARM_REMOVE_COMMAND_H

#include <QDebug>

#include "Command/QmlCommandBase.h"

class AlarmRemoveCommand final : public QmlCommandBase {
public:

    void doExecute(CommandArgs const& data) final;
};

#endif