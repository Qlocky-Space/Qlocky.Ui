#ifndef COMMAND_DISPATCHER_IFC_H
#define COMMAND_DISPATCHER_IFC_H

#include <string>

#include "CommandArgs.h"
#include "CommandIfc.h"

/**
 * Command dispatchor is used for dispatch all registered commands.
 */
class CommandDispatcherIfc {
public:

    /**
     * CommandCode is a type alias.
     * It is used to uniquely identify commands within the command dispatcher.
     */
    using CommandCode = std::string;

    /**
     * Dispatch a command with the given data.
     * @param command The command to execute.
     * @param data The command arguments.
     */
    virtual void dispatch(CommandCode const& id, CommandArgs const* data = nullptr) = 0;

    /**
     * Register a command with the dispatcher.
     * @param id The command identifier.
     * @param command The command to register.
     */
    virtual void reg(CommandCode const& id, CommandIfc& command) = 0;

    virtual ~CommandDispatcherIfc() = default;
};

#endif