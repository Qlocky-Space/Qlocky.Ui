#ifndef NAVIGATE_TO_PAGE_COMMAND_H
#define NAVIGATE_TO_PAGE_COMMAND_H

#include <types/UriQuery.h>

#include "Command/QmlCommandBase.h"
#include "InteractiveNavigatorIfc.h"

/**
 * NavigateToCommand is a command that navigates to a specific page in the application.
 */
class NavigateToCommand final : public QmlCommandBase {
public:

    NavigateToCommand(InteractiveNavigatorIfc& navigator) :
        m_navigator {navigator} {
    }

    /**
     * @see QmlCommandBase::doExecute
     */
    void doExecute(CommandArgs const& data) override {
        UriQuery query {data.get<QString>("uri").toStdString()};
        m_navigator.navigateTo(query);
    }

private:

    InteractiveNavigatorIfc& m_navigator;
};

#endif