#ifndef WIFI_STATUS_EVENT_H
#define WIFI_STATUS_EVENT_H

#include <EventIfc.h>

enum class WifiStatus : uint8_t {
    UP,
    DOWN,
    CONNECTING,
    CONNECTED,
    ERROR
};

class WifiStatusEvent final : public EventIfc {
public:

    WifiStatusEvent() = default;
    ~WifiStatusEvent() final = default;

    /**
     * Constructor for WifiStatusEvent.
     * @param wifiStatus The current WiFi status.
     */
    WifiStatusEvent(WifiStatus wifiStatus) :
        m_wifiStatus(wifiStatus) {
    }

    /**
     * Gets the current WiFi status.
     * @return The current WiFi status.
     */
    WifiStatus getWifiStatus() const {
        return m_wifiStatus;
    }

private:

    WifiStatus m_wifiStatus {WifiStatus::DOWN};
};

#endif