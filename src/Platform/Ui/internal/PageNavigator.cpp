#include "PageNavigator.h"

#include "PageChangedEvent.h"

PageNavigator::PageNavigator(Mediator& mediator) :
    m_mediator {mediator},
    m_pageStack {},
    m_activePage {} {
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
}

Page const& PageNavigator::getActivePage() const {
    return m_activePage;
}

void PageNavigator::changePageTo(Page const& page) {
    m_activePage = page;
    m_mediator.notify(PageChangedEvent(page));
}
