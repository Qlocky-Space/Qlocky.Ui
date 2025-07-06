#include "InteractiveNavigator.h"

#include "Navigation/NavigateToEvent.h"

static Uri::Scheme const QlockyScheme {"qlocky"};

InteractiveNavigator::InteractiveNavigator(Mediator& mediator, InteractiveUriRegistryIfc& registry) :
    m_mediator {mediator},
    m_registry {registry},
    m_uriStack {},
    m_activeUri {} {
}

void InteractiveNavigator::navigateTo(UriQuery const& uri) {
    if (m_activeUri == uri) {
        return;
    }

    m_uriStack.push(m_activeUri);
    changeTo(uri);
}

void InteractiveNavigator::back() {
    if (m_uriStack.empty()) {
        return;
    }

    changeTo(m_uriStack.top());
    m_uriStack.pop();
}

void InteractiveNavigator::changeTo(UriQuery const& query) {
    m_activeUri = query;
    InteractiveMeta meta {m_registry.meta(query.uri())};

    if (query.uri().scheme() == QlockyScheme) {
        m_mediator.notify(NavigateToEvent(query, meta));
    }
    else {
        // Not supported yet
    }
}
