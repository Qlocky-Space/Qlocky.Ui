#include "NetworkForgetCommand.h"

#include <ng-log/logging.h>
#include <string>

NetworkForgetCommand::NetworkForgetCommand(NetworkRepositoryIfc& repository) :
    QmlCommandBase {},
    m_repository {repository} {
}

void NetworkForgetCommand::doExecute(CommandArgs const& data) {
    std::string const ssid {data.get<QString>("ssid").toStdString()};
    if (ssid.empty()) {
        LOG(WARNING) << "NetworkForgetCommand: SSID is required to connect to a network.";
        return;
    }

    m_repository.removeProfile(ssid);
}