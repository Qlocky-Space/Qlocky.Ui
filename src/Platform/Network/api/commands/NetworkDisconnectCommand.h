#ifndef NETWORK_DISCONNECT_TO_COMMAND_H
#define NETWORK_DISCONNECT_TO_COMMAND_H

#include <Command/QmlCommandBase.h>

#include "NetworkServiceIfc.h"

/**
 * Command to disconnect from the current network.
 */
class NetworkDisconnectCommand : public QmlCommandBase {
public:

    explicit NetworkDisconnectCommand(NetworkServiceIfc& networkService);

protected:

    /**
     * @see CommandIfc::doExecute
     */
    void doExecute(CommandArgs const& data) final;

private:

    NetworkServiceIfc& m_networkService;
};

#endif