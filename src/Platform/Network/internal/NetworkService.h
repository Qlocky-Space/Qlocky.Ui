#ifndef QLOCKY_NETWORK_SERVICE_H
#define QLOCKY_NETWORK_SERVICE_H

#include <Mediator.h>

#include "KeyValueDatabaseIfc.h"
#include "NetworkDriverIfc.h"
#include "NetworkDriverListenerIfc.h"
#include "NetworkServiceIfc.h"
#include "NetworkStateMachine.h"
#include "PersistenceKey.h"
#include "PersistenceServiceIfc.h"

/**
 * Network service implementation.
 * A Platform independent service that provides network-related functionalities.
 * This service can be used to enable/disable network, set airplane mode, etc.
 */
class NetworkService final : public NetworkServiceIfc, NetworkDriverListenerIfc {
public:

    /**
     * Constructor for NetworkService.
     * @param mediator The mediator instance used for event notification.
     * @param persistenceService The persistence service instance for data storage.
     * @param networkDriver The network driver instance for managing network operations.
     */
    NetworkService(Mediator& mediator, PersistenceServiceIfc& persistenceService, NetworkDriverIfc& networkDriver);

    ~NetworkService() final = default;

    /**
     * @see NetworkServiceIfc::initialize
     */
    void initialize() final;

    /**
     * @see NetworkServiceIfc::enable
     */
    void enable() final;

    /**
     * @see NetworkServiceIfc::disable
     */
    void disable() final;

    /**
     * @see NetworkServiceIfc::setAirplaneMode
     */
    void setAirplaneMode(bool enabled) final;

    /**
     * @see NetworkDriverListenerIfc::onNetStatusChanged
     */
    void onNetStatusChanged(PhyStatus const status) final;

    /**
     * @see NetworkDriverListenerIfc::onScanCompleted
     */
    void onScanCompleted(bool success) final;

    /**
     * @see NetworkDriverListenerIfc::onScanResultsAvailable
     */
    void onScanResultsAvailable(ScanResult& result) final;

private:

    inline static PersistenceKey const AirplaneModeKey {"AirplaneMode"};
    inline static PersistenceKey const NetworkEnabledKey {"NetworkEnabled"};

    KeyValueDatabaseIfc& getDatabase() {
        return m_persistency.getContext("NetworkService");
    }

    void sendCommunicationStatus();

    Mediator& m_mediator;
    PersistenceServiceIfc& m_persistency;
    NetworkStateMachine m_stateMachine;

    bool m_airplaneMode;
};

#endif
