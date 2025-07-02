#ifndef TIME_CHANGED_EVENT_H
#define TIME_CHANGED_EVENT_H

#include <api/EventIfc.h>
#include <TimeProviderIfc.h>

/**
 * Event which provides the actual unix timestamp
 */
class TimeChangedEvent : public EventIfc {
public:

    /**
     * Constructor
     */
    TimeChangedEvent(DateTime const& value) :
        m_value {value} {
    }

    /**
     * Gets the time changed value
     */
    DateTime getValue() const {
        return m_value;
    }

private:

    DateTime m_value;
};

#endif