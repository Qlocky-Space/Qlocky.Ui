#ifndef SRC_PLATFORM_OS_API_EVENTS_APPLICATION_LIFECYCLE_STATE_CHANGED_EVENT_H
#define SRC_PLATFORM_OS_API_EVENTS_APPLICATION_LIFECYCLE_STATE_CHANGED_EVENT_H

#include "ApplicationLifecycleIfc.h"
#include "EventIfc.h"

/**
 * Event dispatched whenever the application lifecycle state changes.
 */
class ApplicationLifecycleStateChangedEvent final : public EventIfc {
public:

    ApplicationLifecycleStateChangedEvent() = default;
    ~ApplicationLifecycleStateChangedEvent() final = default;

    /**
     * @param previousState State before the transition.
     * @param currentState State after the transition.
     */
    ApplicationLifecycleStateChangedEvent(
        ApplicationLifecycleState previousState,
        ApplicationLifecycleState currentState) :
        m_previousState {previousState},
        m_currentState {currentState} {
    }

    /**
     * @return State before the transition.
     */
    ApplicationLifecycleState previousState() const {
        return m_previousState;
    }

    /**
     * @return State after the transition.
     */
    ApplicationLifecycleState currentState() const {
        return m_currentState;
    }

private:

    ApplicationLifecycleState m_previousState {ApplicationLifecycleState::Startup};
    ApplicationLifecycleState m_currentState {ApplicationLifecycleState::Startup};
};

#endif // SRC_PLATFORM_OS_API_EVENTS_APPLICATION_LIFECYCLE_STATE_CHANGED_EVENT_H
