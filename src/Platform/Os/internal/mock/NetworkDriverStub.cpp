#include "NetworkDriverStub.h"

#include <chrono>

NetworkDriverStub::~NetworkDriverStub() {
    m_scanInProgress.store(false);
    m_connected.store(false);
    m_isUp.store(false);
    joinScanThread();
    joinConnectionThread();
}

NetworkResult NetworkDriverStub::up(std::string const& interfaceName) {
    m_isUp.store(true);
    m_connected.store(false);
    m_scanInProgress.store(false);

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::down() {
    m_scanInProgress.store(false);
    m_connected.store(false);
    m_isUp.store(false);
    joinScanThread();
    joinConnectionThread();

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
    if (!m_isUp.load()) {
        return NetworkResult::success(false);
    }

    bool expected {false};
    if (!m_scanInProgress.compare_exchange_strong(expected, true)) {
        return NetworkResult::success(false);
    }

    joinScanThread();
    notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::SCANNING);

    m_scanThread = std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        bool const shouldPublish {m_isUp.load() && m_scanInProgress.load()};
        m_scanInProgress.store(false);
        if (!shouldPublish) {
            return;
        }

        notify(&NetworkDriverListenerIfc::onScanCompleted, true);
        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, (m_connected.load() ? NetworkIfStatus::CONNECTED : NetworkIfStatus::DISCONNECTED));
    });

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::fetchScanResults() {
    if (!m_isUp.load()) {
        return NetworkResult::success(false);
    }

    for (auto const& network : m_networks) {
        ScanResult result {network.ssid, -60}; // Simulated signal strength
        notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);
    }

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::abortScan() {
    if (!m_isUp.load()) {
        return NetworkResult::success(false);
    }

    bool const wasScanning {m_scanInProgress.exchange(false)};
    if (wasScanning) {
        notify(&NetworkDriverListenerIfc::onScanCompleted, false);
    }

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::connectTo(std::string const& ssid) {
    if (!m_isUp.load()) {
        return NetworkResult::success(false);
    }
    if (ssid.empty()) {
        return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
    }

    bool expected {false};
    if (!m_connected.compare_exchange_strong(expected, true)) {
        return NetworkResult::success(true);
    }

    notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::CONNECTING);
    joinConnectionThread();

    m_connectionThread = std::thread([this, ssid]() {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (!m_connected.load() || !m_isUp.load()) {
            return;
        }

        notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::CONNECTED);

        int32_t signalStrength {-30};
        while (m_connected.load() && m_isUp.load()) {
            ScanResult result {ssid, signalStrength};
            notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);
            signalStrength = -(((-signalStrength + 10) % 50) + 30);

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    return NetworkResult::success(true);
}

NetworkResult NetworkDriverStub::disconnect() {
    if (!m_isUp.load()) {
        return NetworkResult::success(false);
    }

    m_connected.store(false);
    joinConnectionThread();

    notify(&NetworkDriverListenerIfc::onInterfaceStatusChanged, NetworkIfStatus::DISCONNECTED);
    return NetworkResult::success(true);
}

void NetworkDriverStub::joinConnectionThread() {
    if (m_connectionThread.joinable()) {
        m_connectionThread.join();
    }
}

void NetworkDriverStub::joinScanThread() {
    if (m_scanThread.joinable()) {
        m_scanThread.join();
    }
}
