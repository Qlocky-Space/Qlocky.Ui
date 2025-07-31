#ifndef QLOCKY_NETWORK_SERVICE_H
#define QLOCKY_NETWORK_SERVICE_H

#include <Mediator.h>

#include "KeyValueDatabaseIfc.h"
#include "NetworkDriverIfc.h"
#include "NetworkRepositoryIfc.h"
#include "NetworkServiceIfc.h"
#include "NetworkStateMachine.h"
#include "PersistenceKey.h"

/**
 * Network service implementation.
 * A Platform independent service that provides network-related functionalities.
 * This service can be used to enable/disable network, set airplane mode, etc.
 */
class NetworkService final : public NetworkServiceIfc {
public:

    /**
     * Constructor for NetworkService.
     * @param mediator The mediator instance used for event notification.
     * @param repository The network repository instance for managing network profiles.
     * @param networkDriver The network driver instance for managing network operations.
     */
    NetworkService(Mediator& mediator, NetworkRepositoryIfc& repository, NetworkDriverIfc& networkDriver);

    ~NetworkService() final = default;

    /**
     * @see NetworkServiceIfc::initialize
     */
    void initialize() final;

    /**
     * @see NetworkServiceIfc::setAirplaneMode
     */
    void setAirplaneMode(bool enabled) final;

    /**
     * @see NetworkServiceIfc::setWifiEnabled
     */
    void setWifiEnabled(bool enabled) final;

    /**
     * @see NetworkServiceIfc::startScan
     */
    void startScan() final;

    /**
     * @see NetworkServiceIfc::connectTo
     */
    void connectTo(NetworkProfileNew const& profile) final;

    /**
     * @see NetworkServiceIfc::connectTo
     */
    void connectTo(std::string const& ssid) final;

    /**
     * @see NetworkServiceIfc::disconnect
     */
    void disconnect() final;

private:

    void sendCommunicationStatusEvent();

    Mediator& m_mediator;
    NetworkRepositoryIfc& m_repository;
    NetworkStateMachine m_stateMachine;
    NetworkDriverIfc& m_networkDriver;

    bool m_airplaneMode;
};

#endif
