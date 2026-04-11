#ifndef SRC_RADIO_API_EVENTS_STATION_UPDATED_EVENT_H
#define SRC_RADIO_API_EVENTS_STATION_UPDATED_EVENT_H

#include "../StationEntity.h"
#include "EventIfc.h"

/**
 * Event representing that a station was updated.
 */
struct StationUpdatedEvent : public EventIfc {
    StationEntity station;

    explicit StationUpdatedEvent(StationEntity const& station) :
        station {station} {
    }
};

#endif // SRC_RADIO_API_EVENTS_STATION_UPDATED_EVENT_H