#ifndef ALARM_INTERNAL_ALARMUPDATEDEVENT_H
#define ALARM_INTERNAL_ALARMUPDATEDEVENT_H

#include "../AlarmEntity.h"
#include "EventIfc.h"

/**
 * Event representing that an alarm was updated.
 *
 * Contains the updated alarm entity.
 */
struct AlarmUpdatedEvent : public EventIfc {
    AlarmEntity alarm;

    explicit AlarmUpdatedEvent(AlarmEntity const& alarm) :
        alarm {alarm} {
    }
};

#endif