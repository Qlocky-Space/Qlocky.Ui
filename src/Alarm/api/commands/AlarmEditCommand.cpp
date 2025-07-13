#include "AlarmEditCommand.h"

AlarmEditCommand::AlarmEditCommand(CommandDispatcherIfc& dispatcher) :
    m_dispatcher {dispatcher} {
}

void AlarmEditCommand::doExecute(CommandArgs const& data) {
    int const id {data.get<int>("id")};

    CommandArgs args {};
    args.set("uri", "qlocky://alarmDialog?text=Edit " + QString::number(id));
    m_dispatcher.dispatch("nav-to", &args);
}
