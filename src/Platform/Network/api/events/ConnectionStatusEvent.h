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
     */
    ConnectionStatusEvent(uint32_t profileId) :
        m_profileId(profileId) {
    }

    void setFrom(NetworkProfile const& profile) {
        m_profileId = profile.Id;
        m_ssid = profile.Ssid;
        m_signalStrength = profile.SignalStrength;
    }

    /**
     * Returns the profile ID.
     */
    uint32_t profileId() const {
        return m_profileId;
    }

    /**
     * Returns the SSID of the network.
     */
    std::string ssid() const {
        return m_ssid;
    }

    /**
     * Returns the signal strength of the network.
     */
    int32_t signalStrength() const {
        return m_signalStrength;
    }

private:

    uint32_t m_profileId;
    std::string m_ssid;
    int32_t m_signalStrength {-1}; // -1 means no network
};

#endif
