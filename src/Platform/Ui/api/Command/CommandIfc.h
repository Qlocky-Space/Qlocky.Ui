#ifndef QLOCKY_UI_COMMAND_IFC_H
#define QLOCKY_UI_COMMAND_IFC_H

#include "CommandArgs.h"

/**
 * CommandIfc is an interface for commands in the UI framework.
 */
class CommandIfc {
public:

    /**
     * Execute the command.
     * This method should contain the logic to perform the command's action.
     */
    virtual void execute(CommandArgs const* data = nullptr) = 0;

    /**
     * Check if the command can be executed.
     * This method should return true if the command is in a state that allows it to be executed,
     * and false otherwise.
     * @return true if the command can be executed, false otherwise.
     */
    virtual bool canExecute() const = 0;

    CommandIfc() = default;
    virtual ~CommandIfc() = default;
    CommandIfc(CommandIfc const&) = delete;
    CommandIfc& operator=(CommandIfc const&) = delete;
    CommandIfc(CommandIfc&&) = delete;
    CommandIfc& operator=(CommandIfc&&) = delete;
};

#endif