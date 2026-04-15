#ifndef NETWORKPROFILE_INTERNAL_NETWORKPROFILEADDEDEVENT_H
#define NETWORKPROFILE_INTERNAL_NETWORKPROFILEADDEDEVENT_H

#include "../NetworkProfileEntity.h"
#include "EventIfc.h"

/**
 * Event representing that an networkprofile was added.
 *
 * Contains the added networkprofile entity.
 */
struct NetworkProfileAddedEvent : public EventIfc {
    NetworkProfileEntity networkprofile;

    explicit NetworkProfileAddedEvent(NetworkProfileEntity const& networkprofile) :
        networkprofile {networkprofile} {
    }
};

#endif