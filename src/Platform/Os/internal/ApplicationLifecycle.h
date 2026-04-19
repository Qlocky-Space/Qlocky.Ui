#ifndef SRC_PLATFORM_OS_INTERNAL_APPLICATION_LIFECYCLE_H
#define SRC_PLATFORM_OS_INTERNAL_APPLICATION_LIFECYCLE_H

#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

#include "ApplicationLifecycleIfc.h"
#include "DisplayControlIfc.h"
#include "Mediator.h"
#include "StateMachineBase.h"

class ApplicationClosedEvent;
class ApplicationStartedEvent;

/**
 * Tracks application lifecycle and dispatches state transition events.
 */
class ApplicationLifecycle final : public ApplicationLifecycleIfc, private StateMachineBase<ApplicationLifecycleState> {
public:

    /**
     * @param mediator The mediator for event dispatching.
     * @param displayControl Display control for turning display on/off during state transitions.
     */
    ApplicationLifecycle(Mediator& mediator, DisplayControlIfc& displayControl);
    ~ApplicationLifecycle() final;

    /**
     * @see ApplicationLifecycleIfc::initialize
     */
    void initialize() final;

    /**
     * @see ApplicationLifecycleIfc::forceInactive
     */
    void forceInactive() final;

    /**
     * @see ApplicationLifecycleIfc::requestSuspend
     */
    void requestSuspend() final;

    /**
     * @see ApplicationLifecycleIfc::requestWakeup
     */
    void requestWakeup() final;

    /**
     * @see ApplicationLifecycleIfc::requestShutdown
     */
    void requestShutdown() final;

    /**
     * @see ApplicationLifecycleIfc::requestRestart
     */
    void requestRestart() final;

    /**
     * @see ApplicationLifecycleIfc::state
     */
    ApplicationLifecycleState state() const final;

    /**
     * @see ApplicationLifecycleIfc::setInactivityTimeoutSeconds
     */
    void setInactivityTimeoutSeconds(uint32_t timeoutSeconds) final;

    /**
     * @see ApplicationLifecycleIfc::inactivityTimeoutSeconds
     */
    uint32_t inactivityTimeoutSeconds() const final;

private:

    void notifyUserInput();

    void onTransition(ApplicationLifecycleState state) final;
    void onEnterState(ApplicationLifecycleState state) final;
    void onLeaveState(ApplicationLifecycleState state) final;
    void clearFlags() final;

    void runInputWatcherLoop();
    std::vector<int> openInputDeviceHandles() const;
    void closeInputDeviceHandles(std::vector<int>& handles) const;
    void processInputHandles(std::vector<int> const& handles);
    void evaluateInactivityTimeout();
    void processStateMachine();
    void onApplicationStarted(ApplicationStartedEvent const&);
    void onApplicationClosed(ApplicationClosedEvent const&);
    void performRestart();
    void performShutdown();

    Mediator& m_mediator;
    DisplayControlIfc& m_displayControl;
    mutable std::mutex m_mutex {};
    std::thread m_inputWatcher {};
    std::atomic<bool> m_isStopping {false};

    std::chrono::steady_clock::time_point m_lastInputAt {std::chrono::steady_clock::now()};
    std::chrono::steady_clock::time_point m_ignoreWakeInputUntil {std::chrono::steady_clock::time_point::min()};
    std::chrono::milliseconds m_forceInactiveWakeSuppression {std::chrono::milliseconds {500}};
    std::chrono::seconds m_inactivityTimeout {std::chrono::seconds {30}};
    bool m_applicationReady {false};
    bool m_inputDetected {false};
    bool m_inactivityDetected {false};
    bool m_suspendRequested {false};
    bool m_shutdownRequested {false};
    bool m_restartRequested {false};

    ApplicationLifecycleState m_previousState {ApplicationLifecycleState::Startup};
    std::vector<std::pair<ApplicationLifecycleState, ApplicationLifecycleState>> m_pendingEvents {};
};

#endif // SRC_PLATFORM_OS_INTERNAL_APPLICATION_LIFECYCLE_H
