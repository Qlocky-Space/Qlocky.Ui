#ifndef SRC_PLATFORM_OS_API_APPLICATION_LIFECYCLE_IFC_H
#define SRC_PLATFORM_OS_API_APPLICATION_LIFECYCLE_IFC_H

#include <cstdint>

/**
 * Lifecycle states of the running application.
 */
enum class ApplicationLifecycleState {
    /**
     * Initial state during startup sequence before the application becomes ready.
     * This is the default state and cannot be re-entered after leaving it.
     */
    Startup,

    /**
     * Application is loaded and ready for user interaction.
     */
    Active,

    /**
        * Application is running but no user input has been detected for the configured timeout.
     */
    Inactive,

    /**
     * Application is suspended and intended to enter deep sleep.
     * @note Not used at the moment.
     */
    Suspend,

    /**
     * Application shutdown has been requested.
     * @note Request source is not implemented at the moment.
     */
    Shutdown,
};

/**
 * Tracks and exposes the application lifecycle state.
 */
class ApplicationLifecycleIfc {
public:

    virtual ~ApplicationLifecycleIfc() = default;

    /**
     * Starts lifecycle tracking and event dispatching.
     */
    virtual void initialize() = 0;

    /**
     * Request transition to Suspend state.
     * @note The deep sleep behavior is not implemented yet.
     */
    virtual void requestSuspend() = 0;

    /**
     * Force an immediate transition to Inactive state, bypassing the inactivity timeout.
     */
    virtual void forceInactive() = 0;

    /**
    * Request transition to Active state from Inactive.
    * @note This is a placeholder for potential future use cases where an external trigger (e.g. RTC alarm) could wake up the device.
    */
    virtual void requestWakeup() = 0;

    /**
     * Request transition to Shutdown state.
     */
    virtual void requestShutdown() = 0;

    /**
     * Request a system restart.
     */
    virtual void requestRestart() = 0;

    /**
     * Configure timeout before transitioning from Active to Inactive.
     * @param timeoutSeconds Inactivity timeout in seconds.
     */
    virtual void setInactivityTimeoutSeconds(uint32_t timeoutSeconds) = 0;

    /**
     * Returns the currently configured inactivity timeout.
     * @return Inactivity timeout in seconds.
     */
    virtual uint32_t inactivityTimeoutSeconds() const = 0;

    /**
     * Returns the current lifecycle state.
     * @return The current application lifecycle state.
     */
    virtual ApplicationLifecycleState state() const = 0;
};

#endif // SRC_PLATFORM_OS_API_APPLICATION_LIFECYCLE_IFC_H
