#ifndef SRC_RADIO_API_EVENTS_RADIO_FAVORITE_REMOVED_EVENT_H
#define SRC_RADIO_API_EVENTS_RADIO_FAVORITE_REMOVED_EVENT_H

#include "../RadioEntity.h"
#include "EventIfc.h"

struct RadioFavoriteRemovedEvent : public EventIfc {
    RadioId radioId;

    explicit RadioFavoriteRemovedEvent(RadioId radioId) :
        radioId {std::move(radioId)} {
    }
};

#endif // SRC_RADIO_API_EVENTS_RADIO_FAVORITE_REMOVED_EVENT_H
