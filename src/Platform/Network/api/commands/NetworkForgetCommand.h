#ifndef NETWORK_FORGET_COMMAND_H
#define NETWORK_FORGET_COMMAND_H

#include <Command/QmlCommandBase.h>

#include "NetworkRepositoryIfc.h"

/**
 * Command to forget from the current network.
 */
class NetworkForgetCommand : public QmlCommandBase {
public:

    explicit NetworkForgetCommand(NetworkRepositoryIfc& repository);

protected:

    /**
     * @see CommandIfc::doExecute
     */
    void doExecute(CommandArgs const& data) final;

private:

    NetworkRepositoryIfc& m_repository;
};

#endif