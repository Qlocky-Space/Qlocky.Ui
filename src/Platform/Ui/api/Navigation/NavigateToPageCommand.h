#ifndef NAVIGATE_TO_PAGE_COMMAND_H
#define NAVIGATE_TO_PAGE_COMMAND_H

#include "Command/QmlCommandBase.h"
#include "NavigatorIfc.h"

/**
 * NavigateToPageCommand is a command that navigates to a specific page in the application.
 */
class NavigateToPageCommand final : public QmlCommandBase {
public:

    NavigateToPageCommand(NavigatorIfc& navigator) :
        m_navigator {navigator} {
    }

    /**
     * @see QmlCommandBase::doExecute
     */
    void doExecute(CommandArgs const& data) override {
        Page page {};
        page.name = data.get<QString>("pageName").toStdString();
        page.url = data.get<QString>("pageUrl").toStdString();

        m_navigator.navigateTo(page);
    }

private:

    NavigatorIfc& m_navigator;
};

#endif