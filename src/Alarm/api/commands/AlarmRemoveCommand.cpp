#include "AlarmRemoveCommand.h"

AlarmRemoveCommand::AlarmRemoveCommand(AlarmRepositoryIfc& repository) :
    m_repository(repository) {
}

void AlarmRemoveCommand::doExecute(CommandArgs const& data) {
    m_repository.removeAlarm(data.get<int>("id"));
}