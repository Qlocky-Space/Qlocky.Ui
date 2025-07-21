#ifndef APPLICATION_CLOSE_EVENT_H
#define APPLICATION_CLOSE_EVENT_H

#include "../EventIfc.h"

/**
 * ApplicationClosedEvent is an event that is triggered when the application is about to close.
 */
class ApplicationClosedEvent : public EventIfc {
public:

    /**
     * Constructs an ApplicationClosedEvent.
     */
    ApplicationClosedEvent() = default;
};

#endif