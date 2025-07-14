#ifndef ALARM_INTERNAL_ALARMADDEDEVENT_H
#define ALARM_INTERNAL_ALARMADDEDEVENT_H

#include "../AlarmEntity.h"
#include "EventIfc.h"

/**
 * Event representing that an alarm was added.
 *
 * Contains the added alarm entity.
 */
struct AlarmAddedEvent : public EventIfc {
    AlarmEntity alarm;

    explicit AlarmAddedEvent(AlarmEntity const& alarm) :
        alarm {alarm} {
    }
};

#endif