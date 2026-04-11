#ifndef SRC_RADIO_API_EVENTS_STATION_REMOVED_EVENT_H
#define SRC_RADIO_API_EVENTS_STATION_REMOVED_EVENT_H

#include "../StationEntity.h"
#include "EventIfc.h"

/**
 * Event representing that a station was removed.
 */
struct StationRemovedEvent : public EventIfc {
    StationId stationId;

    explicit StationRemovedEvent(StationId const& stationId) :
        stationId {stationId} {
    }
};

#endif // SRC_RADIO_API_EVENTS_STATION_REMOVED_EVENT_H