#ifndef NETWORK_DRIVER_LISTENER_IFC_H
#define NETWORK_DRIVER_LISTENER_IFC_H

#include <cstdint>

enum class NetworkIfStatus : uint8_t {
    DISCONNECTED,
    SCANNING,
    CONNECTED,
    CONNECTING,
    UNKNOWN
};

/**
 * ScanResult represents the result of a Wi-Fi scan.
 */
struct ScanResult {
    std::string ssid;
    int32_t signalStrength;
};

/**
 * NetworkDriverListenerIfc is an interface for listening to network driver events.
 */
class NetworkDriverListenerIfc {
public:

    virtual ~NetworkDriverListenerIfc() = default;

    /**
     * Called when the network status changes.
     * @param status New network status.
     */
    virtual void onInterfaceStatusChanged(NetworkIfStatus const status) = 0;

    /**
     * Called when a network scan is completed.
     * @param success True if the scan was successful, false otherwise.
     */
    virtual void onScanCompleted(bool success) = 0;

    /**
     * Called when scan results are available.
     * @param results Scan results data.
     */
    virtual void onScanResultsAvailable(ScanResult& result) = 0;
};

#endif // NETWORK_DRIVER_LISTENER_IFC_H
