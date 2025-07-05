#ifndef PAGE_CHANGED_EVENT_H
#define PAGE_CHANGED_EVENT_H

#include "api/EventIfc.h"
#include "NavigatorIfc.h"

/**
 * PageChangedEvent is an event that is triggered when the active page changes.
 */
class PageChangedEvent : public EventIfc {
public:

    /**
     * Constructs a PageChangedEvent with the specified page.
     */
    explicit PageChangedEvent(Page const& page) :
        m_activePage {page} {
    }

    /**
     * Returns the page associated with this event.
     *
     * @return The changed page.
     */
    Page getPage() const {
        return m_activePage;
    }

private:

    Page m_activePage;
};

#endif