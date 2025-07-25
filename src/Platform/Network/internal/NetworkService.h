#ifndef QLOCKY_NETWORK_SERVICE_H
#define QLOCKY_NETWORK_SERVICE_H

#include <Mediator.h>

#include "api/NetworkServiceIfc.h"

/**
 * Network service implementation.
 * A Platform independent service that provides network-related functionalities.
 * This service can be used to enable/disable network, set airplane mode, etc.
 */
class NetworkService final : public NetworkServiceIfc {
public:

    NetworkService(Mediator& mediator);

    ~NetworkService() final = default;

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

private:

    void updateNetworkStatus();

    Mediator& m_mediator;
    bool m_serviceEnabled;
    bool m_airplaneMode;
};

#endif
