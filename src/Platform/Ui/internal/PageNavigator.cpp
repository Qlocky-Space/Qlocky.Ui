#include "PageNavigator.h"

#include "Navigation/PageChangedEvent.h"

PageNavigator::PageNavigator(Mediator& mediator) :
    m_mediator {mediator},
    m_pageStack {},
    m_activePage {} {
}

void PageNavigator::navigateToDefault() {
    static Page const DEFAULT_PAGE {"MainPage", "/qt/qml/AppShell/qml/MainPage.qml"};

    // Clear the page stack to ensure we start fresh
    while (!m_pageStack.empty()) {
        m_pageStack.pop();
    }

    changePageTo(DEFAULT_PAGE);
}

void PageNavigator::navigateTo(Page const& page) {
    if (m_activePage == page) {
        return;
    }

    m_pageStack.push(m_activePage);
    changePageTo(page);
}

void PageNavigator::back() {
    if (m_pageStack.empty()) {
        return;
    }

    changePageTo(m_pageStack.top());
    m_pageStack.pop();
}

void PageNavigator::changePageTo(Page const& page) {
    m_activePage = page;
    m_mediator.notify(PageChangedEvent(page));
}
