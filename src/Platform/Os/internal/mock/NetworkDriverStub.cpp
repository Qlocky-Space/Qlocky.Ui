#include "NetworkDriverStub.h"

#include <future>

NetworkDriverStub::~NetworkDriverStub() {
    m_connected = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

NetworkResult NetworkDriverStub::up(std::string const& interfaceName) {
    m_isUp = true;
    m_connected = false;

    m_networks.clear();
    m_networks.push_back(NetworkInfo {"Mock Network 1", "", "WPA-NONE"});
    m_networks.push_back(NetworkInfo {"Mock Network 2", "", "WPA-NONE"});
    m_networks.push_back(NetworkInfo {"Mock Network 3", "", "WPA-NONE"});

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::down() {
    m_connected = false;
    m_isUp = false;

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::registerNetwork(NetworkInfo const& network) {
    m_networks.push_back(network);
    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::unregisterAll() {
    m_networks.clear();
    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::triggerScan() {
    if (!m_isUp) {
        return NetworkResult::success(false);
    }

    [[maybe_unused]] auto future = std::async(std::launch::async, [this]() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        notify(&NetworkDriverListenerIfc::onScanCompleted, true);
    });

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::fetchScanResults() {
    if (!m_isUp) {
        return NetworkResult::success(false);
    }

    for (auto const& network : m_networks) {
        [[maybe_unused]] auto future = std::async(std::launch::async, [this, network]() {
            // simulate random delay for each network
            int delay = rand() % 5 + 1; // Random delay between 1 and 5 seconds
            std::this_thread::sleep_for(std::chrono::seconds(delay));

            ScanResult result {network.ssid, -60}; // Simulated signal strength
            notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);
        });
    }

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::abortScan() {
    if (!m_isUp) {
        return NetworkResult::success(false);
    }

    notify(&NetworkDriverListenerIfc::onScanCompleted, false);
    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::connectTo(std::string const& ssid) {
    if (!m_isUp) {
        return NetworkResult::success(false);
    }
    if (m_connected) {
        return NetworkResult::success(true); // Already connected
    }
    if (ssid.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::CONNECTING);

    m_connected = true;
    m_thread = std::thread([this, ssid]() {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate connection delay

        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::CONNECTED);

        int32_t signalStrength = -30;
        while (m_connected) {
            ScanResult result {ssid, signalStrength};
            notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);
            signalStrength = -(((-signalStrength + 10) % 50) + 30);

            // Simulate ongoing connection status
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::disconnect() {
    if (!m_isUp) {
        return NetworkResult::success(false);
    }

    m_connected = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }

    notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::DISCONNECTED);
    return NetworkResult::success(true);
}
