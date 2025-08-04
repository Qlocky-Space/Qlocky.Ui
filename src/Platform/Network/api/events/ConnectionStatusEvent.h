#ifndef QLOCKY_CONNECTION_STATUS_EVENT_H
#define QLOCKY_CONNECTION_STATUS_EVENT_H

#include <EventIfc.h>
#include <string>

#include "NetworkProfile.h"

/**
 * Network status event class
 */
class ConnectionStatusEvent final : public EventIfc {
public:

    ConnectionStatusEvent() = default;
    ~ConnectionStatusEvent() final = default;

    /**
     * Constructor for ConnectionStatusEvent.
     * @param profile The network profile associated with the connection status.
     */
    ConnectionStatusEvent(NetworkProfile profile) :
        m_profile(profile) {
    }

    /**
     * Returns the profile ID.
     */
    uint32_t profileId() const {
        return m_profile.Id;
    }

    /**
     * Returns the SSID of the network.
     */
    std::string ssid() const {
        return m_profile.Ssid;
    }

    /**
     * Returns the signal strength of the network.
     */
    int32_t signalStrength() const {
        return m_profile.SignalStrength;
    }

    /**
     * Returns the network profile associated with this event.
     */
    NetworkProfile const& networkProfile() const {
        return m_profile;
    }

private:

    NetworkProfile m_profile;
};

#endif
