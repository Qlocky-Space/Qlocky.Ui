#ifndef SRC_PLATFORM_OS_INTERNAL_QLOCKY_DISPLAY_CONTROL_H
#define SRC_PLATFORM_OS_INTERNAL_QLOCKY_DISPLAY_CONTROL_H

#include <sdbus-c++/sdbus-c++.h>

#include <cstdint>
#include <filesystem>

#include "DisplayControlIfc.h"

/**
 * Display control implementation for Raspberry Pi using DRM/KMS.
 *
 * Detects the active DRM connector for diagnostics and forwards power requests
 * to a compositor-side DBus service. Under Wayland, disabling an HDMI output
 * from the client process can tear down the compositor session.
 */
class DisplayControl final : public DisplayControlIfc {
public:

    DisplayControl();
    ~DisplayControl() final;

    /**
     * @see DisplayControlIfc::turnOn
     */
    void turnOn() final;

    /**
     * @see DisplayControlIfc::turnOff
     */
    void turnOff() final;

    /**
     * @see DisplayControlIfc::dim
     */
    void dim(uint8_t level) final;

private:

    bool detectDrmConnector();
    bool waitForPowerService();
    bool requestPowerState(char const* methodName, char const* requestedState);
    bool requestDim(uint8_t level);
    void logUnavailablePowerService(char const* requestedState, std::string const& errorMessage);

    std::filesystem::path m_drmConnectorStatusPath {};
    std::string m_outputName {};
    bool m_hasLoggedUnavailablePowerService {false};
    bool m_hasLoggedPowerServiceAvailable {false};
    bool m_powerServiceConnected {false};
    std::unique_ptr<sdbus::IConnection> m_connection;
    std::unique_ptr<sdbus::IProxy> m_dbusProxy;
    std::unique_ptr<sdbus::IProxy> m_powerProxy;
};

#endif // SRC_PLATFORM_OS_INTERNAL_QLOCKY_DISPLAY_CONTROL_H
