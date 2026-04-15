#ifndef NETWORKPROFILE_INTERNAL_NETWORKPROFILEREMOVEDEVENT_H
#define NETWORKPROFILE_INTERNAL_NETWORKPROFILEREMOVEDEVENT_H

#include "../NetworkProfileEntity.h"
#include "EventIfc.h"

/**
 * Event representing that a network profile was removed.
 */
struct NetworkProfileRemovedEvent : public EventIfc {
    ProfileId id;

    explicit NetworkProfileRemovedEvent(ProfileId const id) :
        id {id} {
    }
};

#endif