#ifndef NAVIGATE_TO_BACK_COMMAND_H
#define NAVIGATE_TO_BACK_COMMAND_H

#include "NavigatorIfc.h"
#include "QmlCommandBase.h"

/**
 * NavigateBackCommand is a command that navigates back to the previous page in the application.
 */
class NavigateBackCommand final : public QmlCommandBase {
public:

    NavigateBackCommand(NavigatorIfc& navigator) :
        m_navigator {navigator} {
    }

    /**
     * @see QmlCommandBase::doExecute
     */
    void doExecute() override {
        m_navigator.back();
    }

private:

    NavigatorIfc& m_navigator;
};

#endif