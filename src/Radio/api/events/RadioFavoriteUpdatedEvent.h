#ifndef SRC_RADIO_API_EVENTS_RADIO_FAVORITE_UPDATED_EVENT_H
#define SRC_RADIO_API_EVENTS_RADIO_FAVORITE_UPDATED_EVENT_H

#include "../RadioEntity.h"
#include "EventIfc.h"

struct RadioFavoriteUpdatedEvent : public EventIfc {
    RadioEntity radio;

    explicit RadioFavoriteUpdatedEvent(RadioEntity const& radio) :
        radio {radio} {
    }
};

#endif // SRC_RADIO_API_EVENTS_RADIO_FAVORITE_UPDATED_EVENT_H
