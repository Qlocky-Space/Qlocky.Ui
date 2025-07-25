#ifndef QLOCKY_NETWORK_SERVICE_IFC_H
#define QLOCKY_NETWORK_SERVICE_IFC_H

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
     * Enables the network service.
     */
    virtual void enable() = 0;

    /**
     * Disables the network service.
     */
    virtual void disable() = 0;

    /**
     * Set the airplane mode state.
     * @param enabled True to enable airplane mode, false to disable it.
     */
    virtual void setAirplaneMode(bool enabled) = 0;
};

#endif
