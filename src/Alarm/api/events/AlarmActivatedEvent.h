#ifndef ALARM_ACTIVATED_EVENT_H
#define ALARM_ACTIVATED_EVENT_H

#include "../AlarmEntity.h"
#include "EventIfc.h"

/**
 * Event that is triggered when an alarm is activated.
 * This event carries the details of the activated alarm.
 */
struct AlarmActivatedEvent : public EventIfc {
    AlarmEntity alarm;

    explicit AlarmActivatedEvent(AlarmEntity const& alarm) :
        alarm {alarm} {
    }
};

#endif