#ifndef ALARM_REMOVE_COMMAND_H
#define ALARM_REMOVE_COMMAND_H

#include <QDebug>

#include "Command/QmlCommandBase.h"
#include "internal/AlarmRepositoryIfc.h"

class AlarmRemoveCommand final : public QmlCommandBase {
public:

    AlarmRemoveCommand(AlarmRepositoryIfc& repository);

    void doExecute(CommandArgs const& data) final;

private:

    AlarmRepositoryIfc& m_repository;
};

#endif