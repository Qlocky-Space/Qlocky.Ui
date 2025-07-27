#ifndef OS_NETWORK_DRIVER_IFC_H
#define OS_NETWORK_DRIVER_IFC_H

#include <string>
#include <types/Result.h>
#include <vector>

#include "NetworkDriverListenerIfc.h"
#include "SubjectIfc.h"

/**
 * A network driver interface for managing Wi-Fi operations.
 * This interface provides methods to trigger Wi-Fi scans and retrieve SSIDs.
 * It is designed to be implemented by platform-specific network drivers.
 */
class NetworkDriverIfc : public SubjectIfc<NetworkDriverListenerIfc> {
public:

    virtual ~NetworkDriverIfc() = default;

    /**
     * Brings the network interface up.
     * This method is used to enable the network interface for communication.
     * @param interfaceName The name of the network interface to bring up.
     * @return ResultVoid indicating success or failure.
     */
    virtual ResultVoid up(std::string const& interfaceName) = 0;

    /**
     * Brings the network interface down.
     * @return ResultVoid indicating success or failure.
     */
    virtual ResultVoid down() = 0;

    /**
     * Triggers a Wi-Fi scan on the interface.
     * @return true if the scan was successfully triggered, false otherwise.
     */
    virtual ResultVoid triggerScan() = 0;

    /**
     * Fetches the results of the last Wi-Fi scan.
     * @return ResultVoid indicating success or failure.
     */
    virtual ResultVoid fetchScanResults() = 0;

    /**
     * Aborts an ongoing Wi-Fi scan.
     * @return ResultVoid indicating success or failure.
     */
    virtual ResultVoid abortScan() = 0;
};

#endif