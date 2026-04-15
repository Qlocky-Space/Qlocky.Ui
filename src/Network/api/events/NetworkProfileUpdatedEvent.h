#ifndef NETWORKPROFILE_INTERNAL_NETWORKPROFILEUPDATEDEVENT_H
#define NETWORKPROFILE_INTERNAL_NETWORKPROFILEUPDATEDEVENT_H

#include "../NetworkProfileEntity.h"
#include "EventIfc.h"

/**
 * Event representing that an networkprofile was updated.
 *
 * Contains the updated networkprofile entity.
 */
struct NetworkProfileUpdatedEvent : public EventIfc {
    NetworkProfileEntity networkprofile;

    explicit NetworkProfileUpdatedEvent(NetworkProfileEntity const& networkprofile) :
        networkprofile {networkprofile} {
    }
};

#endif