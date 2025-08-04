#include "NetworkConnectToCommand.h"

#include <ng-log/logging.h>
#include <string>

#include "NetworkProfileNew.h"

NetworkConnectToCommand::NetworkConnectToCommand(NetworkServiceIfc& networkService, NetworkRepositoryIfc& repository) :
    QmlCommandBase {},
    m_networkService {networkService},
    m_repository {repository} {
}

void NetworkConnectToCommand::doExecute(CommandArgs const& data) {
    std::string const ssid {data.get<QString>("ssid").toStdString()};
    if (ssid.empty()) {
        LOG(WARNING) << "NetworkConnectToCommand: SSID is required to connect to a network.";
        return;
    }

    auto profileCandidate {m_repository.getProfileBySsid(ssid)};
    if (!profileCandidate.has_value()) {
        // TODO open dialog to enter PWD
        return;
    }

    m_networkService.connectTo(ssid);
}