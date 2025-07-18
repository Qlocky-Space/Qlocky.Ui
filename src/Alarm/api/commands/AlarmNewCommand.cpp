#include "AlarmNewCommand.h"

AlarmNewCommand::AlarmNewCommand(CommandDispatcherIfc& dispatcher) :
    m_dispatcher {dispatcher} {
}

void AlarmNewCommand::doExecute(CommandArgs const& data) {
    CommandArgs args {};
    args.set("uri", "qlocky://alarmDialog?alarmId=");
    m_dispatcher.dispatch("nav-to", &args);
}
