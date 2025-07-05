#ifndef UI_PAGE_NAVIGATOR_H
#define UI_PAGE_NAVIGATOR_H

#include <api/Mediator.h>
#include <stack>

#include "NavigatorIfc.h"

/**
 * PageNavigator is responsible for navigating between pages in the application.
 */
class PageNavigator : public NavigatorIfc {
public:

    /**
     * Constructor for PageNavigator.
     */
    PageNavigator(Mediator& mediator);

    /**
     * @see NavigatorIfc::navigateToDefault
     */
    void navigateToDefault() final;

    /**
     * @see NavigatorIfc::navigateTo
     */
    void navigateTo(Page const& page) final;

    /**
     * @see NavigatorIfc::back
     */
    void back() final;

    /**
     * @see NavigatorIfc::getActivePage
     */
    Page const& getActivePage() const final;

private:

    void changePageTo(Page const& page);

    Mediator& m_mediator;
    std::stack<Page> m_pageStack;
    Page m_activePage;
};

#endif