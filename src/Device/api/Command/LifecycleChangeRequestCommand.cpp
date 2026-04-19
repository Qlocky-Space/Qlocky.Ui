#include "LifecycleChangeRequestCommand.h"

#include <ng-log/logging.h>
#include <string>

LifecycleChangeRequestCommand::LifecycleChangeRequestCommand(ApplicationLifecycleIfc& lifecycle) :
    QmlCommandBase {},
    m_lifecycle {lifecycle} {
}

void LifecycleChangeRequestCommand::doExecute(CommandArgs const& data) {
    std::string const requestedState {data.get<QString>("state").toStdString()};
    if (requestedState.empty()) {
        LOG(WARNING) << "LifecycleChangeRequestCommand: state parameter is required.";
        return;
    }

    if (requestedState == "Active") {
        m_lifecycle.requestWakeup();
        return;
    }

    if (requestedState == "Inactive") {
        m_lifecycle.forceInactive();
        return;
    }

    if (requestedState == "Suspend") {
        m_lifecycle.requestSuspend();
        return;
    }

    if (requestedState == "Shutdown") {
        m_lifecycle.requestShutdown();
        return;
    }

    if (requestedState == "Restart") {
        m_lifecycle.requestRestart();
        return;
    }

    LOG(WARNING) << "LifecycleChangeRequestCommand: unsupported state request '" << requestedState << "'.";
}