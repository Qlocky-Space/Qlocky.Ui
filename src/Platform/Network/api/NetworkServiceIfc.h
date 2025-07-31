#ifndef QLOCKY_NETWORK_SERVICE_IFC_H
#define QLOCKY_NETWORK_SERVICE_IFC_H

#include <string>

#include "NetworkProfile.h"
#include "NetworkProfileNew.h"

/**
 * Network service interface.
 * This interface defines the methods that any network service implementation must provide.
 */
class NetworkServiceIfc {
public:

    virtual ~NetworkServiceIfc() = default;

    /**
     * Initializes the network service.
     * This method should be called to set up any necessary resources or configurations
     */
    virtual void initialize() = 0;

    /**
     * Set the airplane mode state.
     * @param enabled True to enable airplane mode, false to disable it.
     */
    virtual void setAirplaneMode(bool enabled) = 0;

    /**
     * Sets the Wi-Fi enabled state.
     * @param enabled True to enable Wi-Fi, false to disable it.
     */
    virtual void setWifiEnabled(bool enabled) = 0;

    /**
     * Start a network scan.
     * The result of the scan will be notified through the NetworkScanResultEvent.
     */
    virtual void startScan() = 0;

    /**
     * Adds a profile to the network service and connect to it.
     * @param profile The network profile to connect to.
     */
    virtual void connectTo(NetworkProfileNew const& profile) = 0;

    /**
     * Connects to a network with the specified SSID.
     * @param ssid The SSID of the network to connect to.
     */
    virtual void connectTo(std::string const& ssid) = 0;

    /**
     * Disconnects from the current network.
     * This method should be called to disconnect from the currently connected network.
     */
    virtual void disconnect() = 0;
};

#endif
