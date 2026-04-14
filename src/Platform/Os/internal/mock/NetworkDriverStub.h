#ifndef OS_NETWORK_DRIVER_STUB_H
#define OS_NETWORK_DRIVER_STUB_H

#include <atomic>
#include <Subject.h>
#include <thread>

#include "NetworkDriverIfc.h"

class NetworkDriverStub : public Subject<NetworkDriverListenerIfc>, public NetworkDriverIfc {
public:

    NetworkDriverStub() = default;
    ~NetworkDriverStub() final;

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

    void joinConnectionThread();
    void joinScanThread();

    std::vector<NetworkInfo> m_networks {};
    std::atomic<bool> m_isUp {false};
    std::atomic<bool> m_connected {false};
    std::atomic<bool> m_scanInProgress {false};
    std::thread m_connectionThread {};
    std::thread m_scanThread {};
};

#endif