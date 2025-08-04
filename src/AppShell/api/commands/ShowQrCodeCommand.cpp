#include "ShowQrCodeCommand.h"

#include <string>

ShowQrCodeCommand::ShowQrCodeCommand(InteractiveNavigatorIfc& navigator) :
    QmlCommandBase(),
    m_navigator(navigator) {
}

void ShowQrCodeCommand::doExecute(CommandArgs const& data) {
    std::string const content {data.get<QString>("content").toStdString()};

    UriQuery uriQuery {"qlocky://qr"};
    uriQuery.addParam("content", content);
    m_navigator.navigateTo(uriQuery);
}