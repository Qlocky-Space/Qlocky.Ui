#ifndef SRC_RADIO_API_EVENTS_RADIO_SELECTION_CHANGED_EVENT_H
#define SRC_RADIO_API_EVENTS_RADIO_SELECTION_CHANGED_EVENT_H

#include <optional>

#include "../RadioEntity.h"
#include "EventIfc.h"

struct RadioSelectionChangedEvent : public EventIfc {
    std::optional<RadioEntity> radio;

    explicit RadioSelectionChangedEvent(std::optional<RadioEntity> const& radio) :
        radio {radio} {
    }
};

#endif // SRC_RADIO_API_EVENTS_RADIO_SELECTION_CHANGED_EVENT_H
