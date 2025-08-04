#ifndef NETWORK_SCAN_EVENT_H
#define NETWORK_SCAN_EVENT_H

#include <EventIfc.h>

/**
 * NetworkScanResultEvent is an event that is emitted when a network scan is completed.
 * It contains the results of the scan, which can be processed by observers.
 */
class NetworkScanEvent final : public EventIfc {
public:

    NetworkScanEvent() = default;
    ~NetworkScanEvent() final = default;

    /**
     * Constructor for NetworkScanEvent.
     * @param scanning True if a scan is in progress, false otherwise.
     */
    NetworkScanEvent(bool const scanning) :
        m_scanning(scanning) {
    }

    /**
     * Returns the scanning state
     * @return True if scanning is in progress, false otherwise.
     */
    bool isScanning() const {
        return m_scanning;
    }

private:

    bool m_scanning {false}; // Indicates if the scan is in progress
};

#endif