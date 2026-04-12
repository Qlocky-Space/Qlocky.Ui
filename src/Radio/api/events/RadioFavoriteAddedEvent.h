#ifndef SRC_RADIO_API_EVENTS_RADIO_FAVORITE_ADDED_EVENT_H
#define SRC_RADIO_API_EVENTS_RADIO_FAVORITE_ADDED_EVENT_H

#include "../RadioEntity.h"
#include "EventIfc.h"

struct RadioFavoriteAddedEvent : public EventIfc {
    RadioEntity radio;

    explicit RadioFavoriteAddedEvent(RadioEntity const& radio) :
        radio {radio} {
    }
};

#endif // SRC_RADIO_API_EVENTS_RADIO_FAVORITE_ADDED_EVENT_H
