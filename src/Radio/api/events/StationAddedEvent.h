#ifndef SRC_RADIO_API_EVENTS_STATION_ADDED_EVENT_H
#define SRC_RADIO_API_EVENTS_STATION_ADDED_EVENT_H

#include "../StationEntity.h"
#include "EventIfc.h"

/**
 * Event representing that a station was added.
 */
struct StationAddedEvent : public EventIfc {
    StationEntity station;

    explicit StationAddedEvent(StationEntity const& station) :
        station {station} {
    }
};

#endif // SRC_RADIO_API_EVENTS_STATION_ADDED_EVENT_H