#include "NetworkConnectToCommand.h"

#include <ng-log/logging.h>
#include <string>

NetworkConnectToCommand::NetworkConnectToCommand(NetworkServiceIfc& networkService, NetworkRepositoryIfc& repository, InteractiveNavigatorIfc& navigator) :
    QmlCommandBase {},
    m_networkService {networkService},
    m_repository {repository},
    m_navigator {navigator} {
}

void NetworkConnectToCommand::doExecute(CommandArgs const& data) {
    std::string const ssid {data.get<QString>("ssid").toStdString()};
    if (ssid.empty()) {
        LOG(WARNING) << "NetworkConnectToCommand: SSID is required to connect to a network.";
        return;
    }

    auto profileCandidate {m_repository.getProfileBySsid(ssid)};
    if (!profileCandidate.has_value()) {
        UriQuery uriQuery {"qlocky://networkProfile"};
        uriQuery.addParam("ssid", ssid);
        m_navigator.navigateTo(uriQuery);
        return;
    }

    m_networkService.connectTo(ssid);
}