#ifndef SRC_RADIO_API_EVENTS_RADIO_PLAYBACK_STATE_CHANGED_EVENT_H
#define SRC_RADIO_API_EVENTS_RADIO_PLAYBACK_STATE_CHANGED_EVENT_H

#include "EventIfc.h"

struct RadioPlaybackStateChangedEvent : public EventIfc {
    bool playing {false};

    explicit RadioPlaybackStateChangedEvent(bool playing) :
        playing {playing} {
    }
};

#endif // SRC_RADIO_API_EVENTS_RADIO_PLAYBACK_STATE_CHANGED_EVENT_H
