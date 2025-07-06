#ifndef UI_PAGE_NAVIGATOR_H
#define UI_PAGE_NAVIGATOR_H

#include <api/Mediator.h>
#include <stack>

#include "Navigation/InteractiveNavigatorIfc.h"
#include "Navigation/InteractiveUriRegistryIfc.h"

/**
 * InteractiveNavigator is responsible for navigating between pages in the application.
 */
class InteractiveNavigator : public InteractiveNavigatorIfc {
public:

    /**
     * Constructor for InteractiveNavigator.
     */
    InteractiveNavigator(Mediator& mediator, InteractiveUriRegistryIfc& registry);

    /**
     * @see InteractiveNavigatorIfc::navigateToDefault
     */
    void navigateToDefault() final;

    /**
     * @see InteractiveNavigatorIfc::navigateTo
     */
    void navigateTo(UriQuery const& uri) final;

    /**
     * @see InteractiveNavigatorIfc::back
     */
    void back() final;

private:

    void changeTo(UriQuery const& page);

    Mediator& m_mediator;
    InteractiveUriRegistryIfc& m_registry;
    std::stack<UriQuery> m_uriStack;
    UriQuery m_activeUri;
};

#endif