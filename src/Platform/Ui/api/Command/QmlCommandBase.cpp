
#include "QmlCommandBase.h"

void QmlCommandBase::execute(CommandArgs const* data) {
    if (canExecute()) {
        static CommandArgs dummy {};
        doExecute(data ? *data : dummy);
    }
}

bool QmlCommandBase::canExecute() const {
    return m_canExecute;
}

void QmlCommandBase::setCanExecute(bool const canExecute) {
    if (m_canExecute != canExecute) {
        m_canExecute = canExecute;
        emit canExecuteChanged();
    }
}
