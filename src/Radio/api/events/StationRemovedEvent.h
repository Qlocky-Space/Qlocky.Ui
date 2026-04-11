#ifndef SRC_RADIO_API_EVENTS_STATION_REMOVED_EVENT_H
#define SRC_RADIO_API_EVENTS_STATION_REMOVED_EVENT_H

#include <types/Uuid.h>

#include "EventIfc.h"

/**
 * Event representing that a station was removed.
 */
struct StationRemovedEvent : public EventIfc {
    Uuid stationId;

    explicit StationRemovedEvent(Uuid const& stationId) :
        stationId {stationId} {
    }
};

#endif // SRC_RADIO_API_EVENTS_STATION_REMOVED_EVENT_H