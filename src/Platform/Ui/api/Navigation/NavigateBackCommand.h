#ifndef NAVIGATE_TO_BACK_COMMAND_H
#define NAVIGATE_TO_BACK_COMMAND_H

#include "Command/QmlCommandBase.h"
#include "InteractiveNavigatorIfc.h"

/**
 * NavigateBackCommand is a command that navigates back to the previous page in the application.
 */
class NavigateBackCommand final : public QmlCommandBase {
public:

    NavigateBackCommand(InteractiveNavigatorIfc& navigator) :
        m_navigator {navigator} {
    }

    /**
     * @see QmlCommandBase::doExecute
     */
    void doExecute(CommandArgs const& data) override {
        m_navigator.back();
    }

private:

    InteractiveNavigatorIfc& m_navigator;
};

#endif