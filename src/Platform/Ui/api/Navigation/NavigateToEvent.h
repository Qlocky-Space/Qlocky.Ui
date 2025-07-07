#ifndef NAVIGATE_TO_EVENT_H
#define NAVIGATE_TO_EVENT_H

#include <types/UriQuery.h>

#include "api/EventIfc.h"
#include "InteractiveUriRegistryIfc.h"

/**
 * NavigateToEvent is an event that is triggered when the active page changes.
 */
class NavigateToEvent : public EventIfc {
public:

    /**
     * Constructs a NavigateToEvent with the specified page.
     */
    explicit NavigateToEvent(UriQuery const& uri, InteractiveMeta const& meta) :
        m_uri {uri},
        m_meta {meta} {
    }

    /**
     * @return the uri associated with this event.
     */
    UriQuery const& getUri() const {
        return m_uri;
    }

    /**
     * @return the meta info where it is navigated to
     */
    InteractiveMeta const& getMeta() const {
        return m_meta;
    }

private:

    UriQuery m_uri;
    InteractiveMeta const& m_meta;
};

#endif