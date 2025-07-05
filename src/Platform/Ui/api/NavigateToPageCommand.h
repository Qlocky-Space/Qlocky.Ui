#ifndef NAVIGATE_TO_PAGE_COMMAND_H
#define NAVIGATE_TO_PAGE_COMMAND_H

#include "NavigatorIfc.h"
#include "QmlCommandBase.h"

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
    void doExecute() override {
        // TODO, use CommandData to pass the page name and URL
        // For now, we just navigate to the Setting page as an example
        Page page {};
        page.name = "Setting";
        page.url = "/qt/qml/AppShell/qml/SettingPage.qml";

        m_navigator.navigateTo(page);
    }

private:

    NavigatorIfc& m_navigator;
};

#endif