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
     * @param wifiMode The current WiFi mode status.
     */
    CommunicationStatusEvent(bool airplaneMode, bool wifiMode) :
        m_airplaneMode(airplaneMode),
        m_wifiMode(wifiMode) {
    }

    /**
     * Gets the current airplane mode status.
     * @return True if airplane mode is enabled, false otherwise.
     */
    bool getAirplaneMode() const {
        return m_airplaneMode;
    }

    /**
     * Gets the current WiFi mode status.
     * @return The current WiFi mode status.
     */
    bool getWifiMode() const {
        return m_wifiMode;
    }

private:

    bool m_airplaneMode {false};
    bool m_wifiMode {false};
};

#endif