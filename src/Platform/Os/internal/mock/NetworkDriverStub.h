#ifndef OS_NETWORK_DRIVER_STUB_H
#define OS_NETWORK_DRIVER_STUB_H

#include <atomic>
#include <Subject.h>
#include <thread>

#include "NetworkDriverIfc.h"

class NetworkDriverStub : public Subject<NetworkDriverListenerIfc>, public NetworkDriverIfc {
public:

    NetworkDriverStub() = default;
    ~NetworkDriverStub() override = default;

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
    NetworkResult up(std::string const& interfaceName) final {
        m_isUp = true;
        m_connected = false;

        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::down
     */
    NetworkResult down() final {
        m_connected = false;
        m_isUp = false;

        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::registerNetwork
     */
    NetworkResult registerNetwork(NetworkInfo const& network) final {
        m_networks.push_back(network);
        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::unregisterAll
     */
    NetworkResult unregisterAll() final {
        m_networks.clear();
        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::triggerScan
     */
    NetworkResult triggerScan() final {
        if (!m_isUp) {
            return NetworkResult::success(false);
        }

        notify(&NetworkDriverListenerIfc::onScanCompleted, true);
        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::fetchScanResults
     */
    NetworkResult fetchScanResults() final {
        if (!m_isUp) {
            return NetworkResult::success(false);
        }

        for (auto const& network : m_networks) {
            ScanResult result {network.ssid, -60}; // Simulated signal strength
            notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);
        }

        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::abortScan
     */
    NetworkResult abortScan() final {
        if (!m_isUp) {
            return NetworkResult::success(false);
        }

        notify(&NetworkDriverListenerIfc::onScanCompleted, false);
        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::connectTo
     */
    NetworkResult connectTo(std::string const& ssid) final {
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

            int32_t signalStrength = -20;
            while (m_connected) {
                // Simulate ongoing connection status
                std::this_thread::sleep_for(std::chrono::seconds(2));

                ScanResult result {ssid, signalStrength};
                notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);
                signalStrength = -((-signalStrength + 10) % 80);
            }
        });

        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::disconnect
     */
    NetworkResult disconnect() final {
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

private:

    std::vector<NetworkInfo> m_networks;
    bool m_isUp {false};
    bool m_connected {false};
    std::thread m_thread {};
};

#endif