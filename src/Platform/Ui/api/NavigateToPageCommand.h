#ifndef NAVIGATE_TO_PAGE_COMMAND_H
#define NAVIGATE_TO_PAGE_COMMAND_H

#include "NavigatorIfc.h"
#include "QmlCommandBase.h"

class NavigateToPageCommand final : public QmlCommandBase {
public:

    NavigateToPageCommand(NavigatorIfc& navigator) :
        m_navigator {navigator} {
    }

    void doExecute() override {
        // TODO
        Page page {};
        page.name = "Setting";
        page.url = "/qt/qml/AppShell/qml/SettingPage.qml";

        m_navigator.navigateTo(page);
    }

private:

    NavigatorIfc& m_navigator;
};

#endif