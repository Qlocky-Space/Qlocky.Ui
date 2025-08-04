#include "NetworkDisconnectCommand.h"

NetworkDisconnectCommand::NetworkDisconnectCommand(NetworkServiceIfc& networkService) :
    QmlCommandBase {},
    m_networkService {networkService} {
}

void NetworkDisconnectCommand::doExecute(CommandArgs const& data) {
    // Call the disconnect method on the network service
    m_networkService.disconnect();
}