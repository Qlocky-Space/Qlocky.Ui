#ifndef NETWORK_SCAN_RESULT_EVENT_H
#define NETWORK_SCAN_RESULT_EVENT_H

#include <EventIfc.h>

#include "NetworkProfile.h"

/**
 * NetworkScanResultEvent is an event that is emitted when a network scan is completed.
 * It contains the results of the scan, which can be processed by observers.
 */
class NetworkScanResultEvent final : public EventIfc {
public:

    NetworkScanResultEvent() = default;
    ~NetworkScanResultEvent() final = default;

    /**
     * Constructor for NetworkScanResultEvent.
     * @param networkInfo The network profile information.
     */
    NetworkScanResultEvent(NetworkProfile const& networkInfo) :
        m_networkInfo(networkInfo) {
    }

    /**
     * Returns the network profile information.
     * @return The network profile as a NetworkProfile object.
     */
    NetworkProfile const& networkProfile() const {
        return m_networkInfo;
    }

private:

    NetworkProfile m_networkInfo;
};

#endif