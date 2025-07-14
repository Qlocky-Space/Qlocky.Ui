#ifndef ALARM_INTERNAL_ALARMREMOVEDEVENT_H
#define ALARM_INTERNAL_ALARMREMOVEDEVENT_H

#include "../AlarmEntity.h"
#include "EventIfc.h"

/**
 * Event representing that an alarm was removed.
 */
struct AlarmRemovedEvent : public EventIfc {
    AlarmId id;

    explicit AlarmRemovedEvent(AlarmId const id) :
        id {id} {
    }
};

#endif