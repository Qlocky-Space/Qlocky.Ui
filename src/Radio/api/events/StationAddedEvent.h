#ifndef SRC_RADIO_API_EVENTS_STATION_ADDED_EVENT_H
#define SRC_RADIO_API_EVENTS_STATION_ADDED_EVENT_H

#include "../StationProfile.h"
#include "EventIfc.h"

/**
 * Event representing that a station was added.
 */
struct StationAddedEvent : public EventIfc {
    StationProfile station;

    explicit StationAddedEvent(StationProfile const& station) :
        station {station} {
    }
};

#endif // SRC_RADIO_API_EVENTS_STATION_ADDED_EVENT_H