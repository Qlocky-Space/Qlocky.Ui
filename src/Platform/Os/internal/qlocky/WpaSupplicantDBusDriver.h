#ifndef WPA_SUPPLICANT_DBUS_DRIVER_H
#define WPA_SUPPLICANT_DBUS_DRIVER_H

#include <Subject.h>

#include "NetworkDriverIfc.h"
#include "NetworkDriverListenerIfc.h"

class WpaSupplicantDBusDriver final : public Subject<NetworkDriverListenerIfc>, public NetworkDriverIfc {
public:

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
};

#endif