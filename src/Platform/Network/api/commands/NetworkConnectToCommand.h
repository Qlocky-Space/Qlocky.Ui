#ifndef NETWORK_CONNECT_TO_COMMAND_H
#define NETWORK_CONNECT_TO_COMMAND_H

#include <Command/QmlCommandBase.h>

#include "NetworkRepositoryIfc.h"
#include "NetworkServiceIfc.h"

/**
 * Command to connect to a network.
 * This command can be used to connect to a network using the specified SSID or a network profile.
 */
class NetworkConnectToCommand : public QmlCommandBase {
public:

    explicit NetworkConnectToCommand(NetworkServiceIfc& networkService, NetworkRepositoryIfc& repository);

protected:

    /**
     * @see CommandIfc::doExecute
     */
    void doExecute(CommandArgs const& data) final;

private:

    NetworkServiceIfc& m_networkService;
    NetworkRepositoryIfc& m_repository;
};

#endif