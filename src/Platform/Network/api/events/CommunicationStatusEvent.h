#ifndef COMMUNICATION_STATUS_EVENT_H
#define COMMUNICATION_STATUS_EVENT_H

#include <EventIfc.h>

class CommunicationStatusEvent final : public EventIfc {
public:

    CommunicationStatusEvent() = default;
    ~CommunicationStatusEvent() final = default;

    /**
     * Constructor for CommunicationStatusEvent.
     * @param airplaneMode The current airplane mode status.
     * @param networkEnabled The current network enabled status.
     */
    CommunicationStatusEvent(bool airplaneMode, bool networkEnabled) :
        m_airplaneMode(airplaneMode),
        m_networkEnabled(networkEnabled) {
    }

    /**
     * Gets the current airplane mode status.
     * @return True if airplane mode is enabled, false otherwise.
     */
    bool getAirplaneMode() const {
        return m_airplaneMode;
    }

    /**
     * Gets the current network enabled status.
     * @return True if network is enabled, false otherwise.
     */
    bool getNetworkEnabled() const {
        return m_networkEnabled;
    }

private:

    bool m_airplaneMode {false};
    bool m_networkEnabled {false};
};

#endif