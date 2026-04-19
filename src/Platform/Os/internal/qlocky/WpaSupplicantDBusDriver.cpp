#include "WpaSupplicantDBusDriver.h"

#include <sdbus-c++/sdbus-c++.h>

#include <mutex>
#include <ng-log/logging.h>

#include "WpaSupplicantHelper.h"

WpaSupplicantDBusDriver::WpaSupplicantDBusDriver() :
    m_connection {sdbus::createSystemBusConnection()},
    m_interfaceName {} {
    m_connection->enterEventLoopAsync();
}

WpaSupplicantDBusDriver::~WpaSupplicantDBusDriver() {
    m_connection->leaveEventLoop();
}

NetworkResult WpaSupplicantDBusDriver::up(std::string const& interfaceName) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    // Workaround:
    // It seems in the RPI image the wifi interface is blocked by rfkill
    // so we need to unblock it before bringing it up
    // This is a workaround, ideally we should not rely on rfkill
    // and instead configure yocto image to not block the interface
    WpaSupplicantHelper::unblockRfkillDevice(WIFI_RFKILL_INDEX);

    if (!WpaSupplicantHelper::wpaSupplicantIsRunning()) {
        LOG(ERROR) << "wpa_supplicant is not running correctly. Cannot bring up interface " << interfaceName;
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_GENERIC);
    }

    m_interfaceName = interfaceName;

    m_proxy = createInterfaceProxy(interfaceName);
    if (!m_proxy) {
        LOG(ERROR) << "Failed to resolve wpa_supplicant interface proxy for " << interfaceName;
        m_interfaceName.clear();
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_GENERIC);
    }

    LOG(INFO) << "Interface " << interfaceName << " is up";

    // if connect to interface, ensure it is never connected
    // auto connect is handled by application itself
    disconnect();
    unregisterAll();

    // register listeners
    m_proxy->uponSignal("PropertiesChanged")
        .onInterface("org.freedesktop.DBus.Properties")
        .call([this](std::string const& interfaceName, std::map<std::string, sdbus::Variant> const& changed, std::vector<std::string> const& invalidated) {
            parseScanningProperty(interfaceName, changed);
            parseStateProperty(interfaceName, changed);
        });
    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::down() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    disconnect();
    unregisterAll();

    m_proxy.reset();
    m_interfaceName.clear();
    LOG(INFO) << "Interface " << m_interfaceName << " is down";

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::registerNetwork(NetworkInfo const& network) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    auto proxy = createInterfaceProxy(m_interfaceName);

    sdbus::ObjectPath networkObj {};
    std::map<std::string, sdbus::Variant> args {};
    // https://w1.fi/cgit/hostap/plain/wpa_supplicant/wpa_supplicant.conf
    args["ssid"] = sdbus::Variant(std::vector<uint8_t>(network.ssid.begin(), network.ssid.end()));
    args["key_mgmt"] = sdbus::Variant(network.keyMgmnt);
    if (network.pskEncrypted()) {
        args["psk"] = sdbus::Variant(network.pskBytes());
    }
    else {
        args["psk"] = sdbus::Variant(network.psk());
    }

    proxy->callMethod("AddNetwork")
        .onInterface("fi.w1.wpa_supplicant1.Interface")
        .withArguments(args)
        .storeResultsTo(networkObj);

    m_networks[network.ssid] = networkObj;

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::unregisterAll() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    auto proxy = createInterfaceProxy(m_interfaceName);
    proxy->callMethod("RemoveAllNetworks")
        .onInterface("fi.w1.wpa_supplicant1.Interface");

    m_networks.clear();
    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::triggerScan() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    auto proxy = createInterfaceProxy(m_interfaceName);

    LOG(INFO) << "Triggering scan on interface " << m_interfaceName;

    std::map<std::string, sdbus::Variant> scanArgs {};
    scanArgs["Type"] = sdbus::Variant(std::string("passive"));

    proxy->callMethod("Scan")
        .onInterface("fi.w1.wpa_supplicant1.Interface")
        .withArguments(scanArgs);

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::fetchScanResults() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
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
    std::lock_guard<std::recursive_mutex> lock(m_mutex);
    // It seems RPI driver doesn not support scan abort
    return NetworkResult::error(NetworkDriverErrorCode::ERROR_NOT_SUPPORTED);
}

NetworkResult WpaSupplicantDBusDriver::connectTo(std::string const& ssid) {
    std::unique_lock<std::recursive_mutex> lock(m_mutex, std::try_to_lock);
    if (!lock.owns_lock()) {
        // Avoid deadlock on re-entrant calls from DBus signal callbacks.
        return NetworkResult::success(true);
    }

    if (ssid.empty() || m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }
    if (m_networks.find(ssid) == m_networks.end()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    auto networkProxy = createNetworkProxy(ssid);

    LOG(INFO) << "Connecting to network: " << ssid;

    try {
        networkProxy->setProperty("Enabled")
            .onInterface("fi.w1.wpa_supplicant1.Network")
            .toValue(sdbus::Variant(true));
    }
    catch (std::exception const& e) {
        LOG(ERROR) << "Failed to enable network " << ssid << ": " << e.what();
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_GENERIC);
    }

    return NetworkResult::success(true);
}

NetworkResult WpaSupplicantDBusDriver::disconnect() {
    std::unique_lock<std::recursive_mutex> lock(m_mutex, std::try_to_lock);
    if (!lock.owns_lock()) {
        // Avoid deadlock on re-entrant calls from DBus signal callbacks.
        return NetworkResult::success(true);
    }

    if (m_interfaceName.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    LOG(INFO) << "Disconnecting from network";

    auto proxy = createInterfaceProxy(m_interfaceName);
    try {
        proxy->callMethod("Disconnect")
            .onInterface("fi.w1.wpa_supplicant1.Interface");
    }
    catch (sdbus::Error const& e) {
        return NetworkResult::success(false);
    }

    return NetworkResult::success(true);
}

std::unique_ptr<sdbus::IProxy> WpaSupplicantDBusDriver::createInterfaceProxy(std::string const& interfaceName) {
    std::unique_ptr<sdbus::IProxy> supplicant;
    try {
        supplicant = sdbus::createProxy(*m_connection, DEFAULT_DBUS_SUPPLICANT_NAME, DEFAULT_DBUS_SUPPLICANT_PATH);
    }
    catch (std::exception const& e) {
        LOG(ERROR) << "Failed to create supplicant proxy: " << e.what();
        return {};
    }

    sdbus::ObjectPath ifacePath {};
    try {
        supplicant->callMethod("GetInterface")
            .onInterface(DEFAULT_DBUS_SUPPLICANT_NAME)
            .withArguments(interfaceName)
            .storeResultsTo(ifacePath);
    }
    catch (std::exception const& e) {
        LOG(ERROR) << "Failed to resolve interface " << interfaceName << ": " << e.what();
        return {};
    }

    if (ifacePath.empty()) {
        LOG(ERROR) << "Empty interface path for interface " << interfaceName;
        return {};
    }

    try {
        auto proxy = sdbus::createProxy(*m_connection, DEFAULT_DBUS_SUPPLICANT_NAME, ifacePath);
        return proxy;
    }
    catch (std::exception const& e) {
        LOG(ERROR) << "Failed to create interface proxy: " << e.what();
        return {};
    }
}

std::unique_ptr<sdbus::IProxy> WpaSupplicantDBusDriver::createNetworkProxy(std::string const& ssid) {
    auto proxy = createInterfaceProxy(m_interfaceName);
    if (!proxy) {
        LOG(ERROR) << "Failed to create interface proxy for " << m_interfaceName;
        return {};
    }
    auto it = m_networks.find(ssid);
    if (it == m_networks.end()) {
        LOG(ERROR) << "Unknown SSID: " << ssid;
        return {};
    }
    sdbus::ObjectPath networkObj {it->second};
    try {
        proxy->callMethod("SelectNetwork")
            .onInterface("fi.w1.wpa_supplicant1.Interface")
            .withArguments(networkObj);
    }
    catch (std::exception const& e) {
        LOG(ERROR) << "Failed to select network " << ssid << ": " << e.what();
        return {};
    }
    try {
        auto networkProxy = sdbus::createProxy(*m_connection, DEFAULT_DBUS_SUPPLICANT_NAME, networkObj);
        return networkProxy;
    }
    catch (std::exception const& e) {
        LOG(ERROR) << "Failed to create network proxy: " << e.what();
        return {};
    }
}

void WpaSupplicantDBusDriver::parseNetworkState(std::string const& state) {
    if (state == "completed") {
        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::CONNECTED);
    }
    else if (state == "scanning") {
        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::SCANNING);
    }
    else if (state == "authenticating" ||
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

void WpaSupplicantDBusDriver::parseScanningProperty(std::string const& interfaceName, std::map<std::string, sdbus::Variant> const& changed) {
    if (interfaceName != "fi.w1.wpa_supplicant1.Interface") {
        return;
    }

    auto it = changed.find("Scanning");
    if (it != changed.end()) {
        bool scanning = it->second.get<bool>();
        if (!scanning) {
            notify(&NetworkDriverListenerIfc::onScanCompleted, true);
        }
    }
}

void WpaSupplicantDBusDriver::parseStateProperty(std::string const& interfaceName, std::map<std::string, sdbus::Variant> const& changed) {
    if (interfaceName != "fi.w1.wpa_supplicant1.Interface") {
        return;
    }

    auto it = changed.find("State");
    if (it != changed.end()) {
        std::string state = it->second.get<std::string>();
        parseNetworkState(state);
    }
}
