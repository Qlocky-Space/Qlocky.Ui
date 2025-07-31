#ifndef WPA_SUPPLICANT_DBUS_DRIVER_H
#define WPA_SUPPLICANT_DBUS_DRIVER_H

#include <sdbus-c++/sdbus-c++.h>

#include <map>
#include <Subject.h>

#include "NetworkDriverIfc.h"
#include "NetworkDriverListenerIfc.h"

/**
 * https://w1.fi/wpa_supplicant/devel/dbus.html#dbus_interface
 *
 * https://dbus.freedesktop.org/doc/dbus-specification.html#basic-types
 */
class WpaSupplicantDBusDriver final : public Subject<NetworkDriverListenerIfc>, public NetworkDriverIfc {
public:

    WpaSupplicantDBusDriver();
    ~WpaSupplicantDBusDriver() final;

    /**
     * @see SubjectIfc::attach
     * @note Required for Boost.DI to resolve the interface.
     */
    void attach(NetworkDriverListenerIfc* observer) final {
        Subject<NetworkDriverListenerIfc>::attach(observer);
    }

    /**
     * @see SubjectIfc::detach
     * @note Required for Boost.DI to resolve the interface.
     */
    void detach(NetworkDriverListenerIfc* observer) final {
        Subject<NetworkDriverListenerIfc>::detach(observer);
    }

    /**
     * @see NetworkDriverIfc::up
     */
    NetworkResult up(std::string const& interfaceName) final;

    /**
     * @see NetworkDriverIfc::down
     */
    NetworkResult down() final;

    /**
     * @see NetworkDriverIfc::registerNetwork
     */
    NetworkResult registerNetwork(NetworkInfo const& network) final;

    /**
     * @see NetworkDriverIfc::unregisterAll
     */
    NetworkResult unregisterAll() final;

    /**
     * @see NetworkDriverIfc::triggerScan
     */
    NetworkResult triggerScan() final;

    /**
     * @see NetworkDriverIfc::fetchScanResults
     */
    NetworkResult fetchScanResults() final;

    /**
     * @see NetworkDriverIfc::abortScan
     */
    NetworkResult abortScan() final;

    /**
     * @see NetworkDriverIfc::connectTo
     */
    NetworkResult connectTo(std::string const& ssid) final;

    /**
     * @see NetworkDriverIfc::disconnect
     */
    NetworkResult disconnect() final;

private:

    static constexpr uint32_t WIFI_RFKILL_INDEX {1};

    inline static sdbus::ServiceName const DEFAULT_DBUS_SUPPLICANT_NAME {"fi.w1.wpa_supplicant1"};
    inline static sdbus::ObjectPath const DEFAULT_DBUS_SUPPLICANT_PATH {"/fi/w1/wpa_supplicant1"};

    std::unique_ptr<sdbus::IProxy> createInterfaceProxy(std::string const& interfaceName);
    std::unique_ptr<sdbus::IProxy> createNetworkProxy(std::string const& ssid);

    void parseNetworkState(std::string const& state);
    void parseScanningProperty(std::string const& interfaceName, std::map<std::string, sdbus::Variant> const& changed);
    void parseStateProperty(std::string const& interfaceName, std::map<std::string, sdbus::Variant> const& changed);

    std::unique_ptr<sdbus::IConnection> m_connection;
    std::unique_ptr<sdbus::IProxy> m_proxy;

    std::map<std::string, sdbus::ObjectPath> m_networks;
    std::string m_interfaceName;
};

#endif