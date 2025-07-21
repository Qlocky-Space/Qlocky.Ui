#ifndef APPLICATION_STARTED_EVENT_H
#define APPLICATION_STARTED_EVENT_H

#include "../EventIfc.h"

/**
 * ApplicationStartedEvent is an event that is triggered when the application is started.
 */
class ApplicationStartedEvent : public EventIfc {
public:

    /**
     * Constructs an ApplicationStartedEvent.
     */
    ApplicationStartedEvent() = default;
};

#endif