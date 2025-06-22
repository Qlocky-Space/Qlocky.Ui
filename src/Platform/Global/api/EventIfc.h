#ifndef PLATFORM_GLOBAL_API_EVENTIFC_H
#define PLATFORM_GLOBAL_API_EVENTIFC_H

/**
 * This interface should be extended by all event types used in the event bus or mediator system.
 * It provides a uniform structure for dispatching and introspection, enabling polymorphic event handling.
 */
class EventIfc {
public:

    virtual ~EventIfc() = default;
};

#endif