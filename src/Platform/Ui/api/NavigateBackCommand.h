#ifndef NAVIGATE_TO_BACK_COMMAND_H
#define NAVIGATE_TO_BACK_COMMAND_H

#include "NavigatorIfc.h"
#include "QmlCommandBase.h"

class NavigateBackCommand final : public QmlCommandBase {
public:

    NavigateBackCommand(NavigatorIfc& navigator) :
        m_navigator {navigator} {
    }

    void doExecute() override {
        m_navigator.back();
    }

private:

    NavigatorIfc& m_navigator;
};

#endif