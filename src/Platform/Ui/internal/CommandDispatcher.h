#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include <map>

#include "Command/CommandDispatcherIfc.h"

/**
 * @see CommandDispatcherIfc
 */
class CommandDispatcher final : public CommandDispatcherIfc {
public:

    CommandDispatcher() = default;

    /**
     * @see CommandDispatcherIfc::dispatch
     */
    void dispatch(CommandCode const& id, CommandArgs const* data = nullptr) final;

    /**
     * @see CommandDispatcherIfc::reg
     */
    void reg(CommandCode const& id, CommandIfc& command) final;

private:

    bool keyExists(CommandCode const& id) const;

    std::map<CommandCode, CommandIfc&> m_commands {};
};

#endif