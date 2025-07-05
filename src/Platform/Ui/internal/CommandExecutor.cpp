#include "CommandExecutor.h"

CommandExecutor::CommandExecutor(CommandDispatcherIfc& dispatcher) :
    m_dispatcher {dispatcher} {
}

void CommandExecutor::dispatch(QString const& id, QVariantMap const& data) {
    CommandArgs args {CommandArgs::fromQVariantMap(data)};

    m_dispatcher.dispatch(id.toStdString(), &args);
}
