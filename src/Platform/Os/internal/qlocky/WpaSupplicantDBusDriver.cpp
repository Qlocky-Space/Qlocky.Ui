#include "WpaSupplicantDBusDriver.h"

#include <sdbus-c++/sdbus-c++.h>

#include <iostream>

WpaSupplicantDBusDriver::WpaSupplicantDBusDriver() :
    m_connection {sdbus::createSystemBusConnection()},
    m_interfaceName {} {

    m_connection->enterEventLoopAsync();
}

WpaSupplicantDBusDriver::~WpaSupplicantDBusDriver() {
    m_connection->leaveEventLoop();
}

NetworkResult WpaSupplicantDBusDriver::up(std::string const& interfaceName) {
    if (interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    m_interfaceName = interfaceName;

    std::cout << "Bringing up interface: " << m_interfaceName << std::endl;

    // register listeners
    m_proxy = createInterfaceProxy(interfaceName);

    m_proxy->uponSignal("PropertiesChanged")
        .onInterface("org.freedesktop.DBus.Properties")
        .call([this](std::string const& interfaceName, std::map<std::string, sdbus::Variant> const& changed, std::vector<std::string> const& invalidated) {
            // std::cout << "Properties changed for interface: " << interfaceName << std::endl;
            // for (auto const& [key, value] : changed) {
            //     std::cout << "  " << key << std::endl;
            // }

            if (interfaceName == "fi.w1.wpa_supplicant1.Interface") {
                auto it = changed.find("Scanning");
                if (it != changed.end()) {
                    bool scanning = it->second.get<bool>();
                    if (!scanning) {
                        notify(&NetworkDriverListenerIfc::onScanCompleted, true);
                    }
                }

                it = changed.find("State");
                if (it != changed.end()) {
                    std::string state = it->second.get<std::string>();
                    parseNetworkState(state);
                }
            }
        });
    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::down() {
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    std::cout << "Bringing down interface: " << m_interfaceName << std::endl;

    m_proxy.reset();

    // auto proxy = createInterfaceProxy(m_interfaceName);
    // proxy->callMethod("Set")
    //     .onInterface("org.freedesktop.DBus.Properties")
    //     .withArguments("fi.w1.wpa_supplicant1.Network", "Enabled", sdbus::Variant(false));

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::registerNetwork(NetworkInfo const& network) {
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    std::cout << "Registering network: " << network.ssid << " on interface: " << m_interfaceName << std::endl;

    auto proxy = createInterfaceProxy(m_interfaceName);

    sdbus::ObjectPath networkObj {};
    std::map<std::string, sdbus::Variant> args {};
    // https://w1.fi/cgit/hostap/plain/wpa_supplicant/wpa_supplicant.conf
    args["ssid"] = sdbus::Variant(std::vector<uint8_t>(network.ssid.begin(), network.ssid.end()));
    args["key_mgmt"] = sdbus::Variant(network.keyMgmnt);
    args["psk"] = sdbus::Variant(network.psk);

    proxy->callMethod("AddNetwork")
        .onInterface("fi.w1.wpa_supplicant1.Interface")
        .withArguments(args)
        .storeResultsTo(networkObj);

    m_networks[network.ssid] = networkObj;

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::triggerScan() {
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    std::cout << "Triggering scan on interface: " << m_interfaceName << std::endl;

    auto proxy = createInterfaceProxy(m_interfaceName);

    std::map<std::string, sdbus::Variant> scanArgs {};
    scanArgs["Type"] = sdbus::Variant(std::string("passive"));

    proxy->callMethod("Scan")
        .onInterface("fi.w1.wpa_supplicant1.Interface")
        .withArguments(scanArgs);

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::fetchScanResults() {
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }
    auto proxy = createInterfaceProxy(m_interfaceName);

    std::vector<sdbus::ObjectPath> bssPaths {proxy->getProperty("BSSs")
            .onInterface("fi.w1.wpa_supplicant1.Interface")
            .get<std::vector<sdbus::ObjectPath>>()};

    for (auto const& bssPath : bssPaths) {
        auto bssProxy = sdbus::createProxy(proxy->getConnection(), DEFAULT_DBUS_SUPPLICANT_NAME, bssPath);

        auto ssid = bssProxy->getProperty("SSID").onInterface("fi.w1.wpa_supplicant1.BSS");
        auto signal = bssProxy->getProperty("Signal").onInterface("fi.w1.wpa_supplicant1.BSS");

        ScanResult result;
        auto ssidRaw {ssid.get<std::vector<uint8_t>>()};
        result.ssid = std::string(ssidRaw.begin(), ssidRaw.end());
        result.signalStrength = signal.get<int16_t>();

        notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);
    }

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::abortScan() {
    // It seems RPI driver doesn not support scan abort
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}

NetworkResult WpaSupplicantDBusDriver::connectTo(std::string const& ssid) {
    if (ssid.empty() || m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }
    if (m_networks.find(ssid) == m_networks.end()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    auto networkProxy = createNetworkProxy(ssid);

    networkProxy->setProperty("Enabled")
        .onInterface("fi.w1.wpa_supplicant1.Network")
        .toValue(sdbus::Variant(true));

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::disconnect() {
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    auto proxy = createInterfaceProxy(m_interfaceName);
    proxy->callMethod("Disconnect")
        .onInterface("fi.w1.wpa_supplicant1.Interface")
        .dontExpectReply();

    return NetworkResult::success(true);
}

std::unique_ptr<sdbus::IProxy> WpaSupplicantDBusDriver::createInterfaceProxy(std::string const& interfaceName) {
    std::unique_ptr<sdbus::IProxy> supplicant {sdbus::createProxy(*m_connection, DEFAULT_DBUS_SUPPLICANT_NAME, DEFAULT_DBUS_SUPPLICANT_PATH)};

    sdbus::ObjectPath ifacePath {};
    supplicant->callMethod("GetInterface")
        .onInterface(DEFAULT_DBUS_SUPPLICANT_NAME)
        .withArguments(interfaceName)
        .storeResultsTo(ifacePath);

    if (ifacePath.empty()) {
        return {};
    }

    return sdbus::createProxy(*m_connection, DEFAULT_DBUS_SUPPLICANT_NAME, ifacePath);
}

std::unique_ptr<sdbus::IProxy> WpaSupplicantDBusDriver::createNetworkProxy(std::string const& ssid) {
    auto proxy = createInterfaceProxy(m_interfaceName);
    sdbus::ObjectPath networkObj {m_networks.find(ssid)->second};

    proxy->callMethod("SelectNetwork")
        .onInterface("fi.w1.wpa_supplicant1.Interface")
        .withArguments(networkObj);

    auto networkProxy = sdbus::createProxy(*m_connection, DEFAULT_DBUS_SUPPLICANT_NAME, networkObj);

    return networkProxy;
}

void WpaSupplicantDBusDriver::parseNetworkState(std::string const& state) {
    std::cout << "Interface state changed: " << state << std::endl;

    if (state == "completed") {
        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::CONNECTED);
    }
    else if (state == "scanning" ||
        state == "authenticating" ||
        state == "4way_handshake" ||
        state == "group_handshake" ||
        state == "associating" ||
        state == "associated") {
        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::CONNECTING);
    }
    else if (state == "disconnected" || state == "inactive") {
        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::DISCONNECTED);
    }
    else {
        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::UNKNOWN);
    }
}
