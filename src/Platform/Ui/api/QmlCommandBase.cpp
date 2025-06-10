
#include "QmlCommandBase.h"

void QmlCommandBase::execute() {
    if (canExecute()) {
        doExecute();
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
