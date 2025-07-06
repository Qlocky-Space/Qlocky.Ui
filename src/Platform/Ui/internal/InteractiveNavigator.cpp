#include "InteractiveNavigator.h"

#include "Navigation/NavigateToEvent.h"

static Uri::Scheme const QlockyScheme {"qlocky"};

InteractiveNavigator::InteractiveNavigator(Mediator& mediator, InteractiveUriRegistryIfc& registry) :
    m_mediator {mediator},
    m_registry {registry} {
}

void InteractiveNavigator::navigateTo(UriQuery const& query) {
    InteractiveMeta meta {m_registry.meta(query.uri())};

    if (query.uri().scheme() == QlockyScheme) {
        m_mediator.notify(NavigateToEvent(query, meta));
    }
    else {
        // Not supported yet
    }
}
