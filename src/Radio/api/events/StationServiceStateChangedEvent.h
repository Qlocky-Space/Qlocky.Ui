#ifndef SRC_RADIO_API_EVENTS_STATION_SERVICE_STATE_CHANGED_EVENT_H
#define SRC_RADIO_API_EVENTS_STATION_SERVICE_STATE_CHANGED_EVENT_H

#include "EventIfc.h"

/**
 * Event representing a station service lifecycle state change.
 */
struct StationServiceStateChangedEvent : public EventIfc {
    enum class State {
        Updating,
        Canceled,
        Finished,
    };

    State state;

    explicit StationServiceStateChangedEvent(State state) :
        state {state} {
    }
};

#endif // SRC_RADIO_API_EVENTS_STATION_SERVICE_STATE_CHANGED_EVENT_H