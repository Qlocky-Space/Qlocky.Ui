#ifndef OS_NETWORK_DRIVER_STUB_H
#define OS_NETWORK_DRIVER_STUB_H

#include <Subject.h>

#include "NetworkDriverIfc.h"

class NetworkDriverStub : public Subject<NetworkDriverListenerIfc>, public NetworkDriverIfc {
public:

    NetworkDriverStub() = default;
    ~NetworkDriverStub() override = default;

    /**
     * @see NetworkDriverIfc::up
     */
    NetworkResult up(std::string const& interfaceName) final {
        m_isUp = true;
        notify(&NetworkDriverListenerIfc::onNetStatusChanged, NetworkStatus::UP);
        return NetworkResult::success(true);
    }

    /**
     * @see NetworkDriverIfc::down
     */
    NetworkResult down() final {
        m_isUp = false;
        notify(&NetworkDriverListenerIfc::onNetStatusChanged, NetworkStatus::DOWN);
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

        ScanResult result {"TestSSID", -50};
        notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);

        ScanResult result {"TestSSID1", -79};
        notify(&NetworkDriverListenerIfc::onScanResultsAvailable, result);

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

        if (ssid.empty()) {
            return NetworkResult::error(NetworkDriverErrorCode::ERROR_INVALID_ARGUMENT);
        }

        notify(&NetworkDriverListenerIfc::onNetStatusChanged, NetworkStatus::CONNECTED);

        return NetworkResult::success(true);
    }

private:

    bool m_isUp {false};
};

#endif