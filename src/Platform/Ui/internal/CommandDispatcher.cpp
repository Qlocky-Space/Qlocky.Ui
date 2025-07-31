#include "CommandDispatcher.h"

#include <ng-log/logging.h>

void CommandDispatcher::dispatch(CommandCode const& id, CommandArgs const* data) {
    if (!keyExists(id)) {
        return;
    }

    DLOG(INFO) << "Executing command with ID: " << id;
    m_commands.at(id).execute(data);
}

void CommandDispatcher::reg(CommandCode const& id, CommandIfc& command) {
    if (keyExists(id)) {
        // Key alredy registerd
        return;
    }

    m_commands.emplace(id, command);
}

bool CommandDispatcher::keyExists(CommandCode const& id) const {
    return m_commands.find(id) != m_commands.end();
}
