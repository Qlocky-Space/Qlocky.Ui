#include "ApplicationLifecycle.h"

#include <array>
#include <chrono>
#include <fcntl.h>
#include <filesystem>
#include <linux/input.h>
#include <ng-log/logging.h>
#include <poll.h>
#include <string>
#include <unistd.h>
#include <vector>

#include "events/ApplicationClosedEvent.h"
#include "events/ApplicationLifecycleStateChangedEvent.h"
#include "events/ApplicationStartedEvent.h"

namespace {

char const* stateToString(ApplicationLifecycleState state) {
    switch (state) {
        case ApplicationLifecycleState::Startup:
            return "Startup";
        case ApplicationLifecycleState::Active:
            return "Active";
        case ApplicationLifecycleState::Inactive:
            return "Inactive";
        case ApplicationLifecycleState::Suspend:
            return "Suspend";
        case ApplicationLifecycleState::Shutdown:
            return "Shutdown";
    }
    return "Unknown";
}

} // namespace

ApplicationLifecycle::ApplicationLifecycle(Mediator& mediator) :
    m_mediator {mediator} {
    m_mediator.subscribe<ApplicationStartedEvent>(this, &ApplicationLifecycle::onApplicationStarted);
    m_mediator.subscribe<ApplicationClosedEvent>(this, &ApplicationLifecycle::onApplicationClosed);
}

ApplicationLifecycle::~ApplicationLifecycle() {
    m_isStopping.store(true);
    if (m_inputWatcher.joinable()) {
        m_inputWatcher.join();
    }
}

void ApplicationLifecycle::initialize() {
    m_lastInputAt = std::chrono::steady_clock::now();

    m_inputWatcher = std::thread([this]() {
        runInputWatcherLoop();
    });
}

ApplicationLifecycleState ApplicationLifecycle::state() const {
    std::lock_guard<std::mutex> const lock {m_mutex};
    return currentState();
}

void ApplicationLifecycle::setInactivityTimeoutSeconds(uint32_t timeoutSeconds) {
    std::lock_guard<std::mutex> const lock {m_mutex};
    m_inactivityTimeout = std::chrono::seconds {timeoutSeconds};
}

uint32_t ApplicationLifecycle::inactivityTimeoutSeconds() const {
    std::lock_guard<std::mutex> const lock {m_mutex};
    return static_cast<uint32_t>(m_inactivityTimeout.count());
}

void ApplicationLifecycle::notifyUserInput() {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        m_lastInputAt = std::chrono::steady_clock::now();
        m_inputDetected = true;
    }

    processStateMachine();
}

void ApplicationLifecycle::forceInactive() {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        m_inactivityDetected = true;
    }

    processStateMachine();
}

void ApplicationLifecycle::requestSuspend() {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        m_suspendRequested = true;
    }

    processStateMachine();
}

void ApplicationLifecycle::requestWakeup() {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        m_inputDetected = true;
    }

    processStateMachine();
}

void ApplicationLifecycle::requestShutdown() {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        m_shutdownRequested = true;
    }

    processStateMachine();
}

void ApplicationLifecycle::onTransition(ApplicationLifecycleState state) {
    switch (state) {
        case ApplicationLifecycleState::Startup:
            transitionByCondition(m_applicationReady, ApplicationLifecycleState::Active);
            break;
        case ApplicationLifecycleState::Active:
            transitionByCondition(m_inactivityDetected, ApplicationLifecycleState::Inactive);
            transitionByCondition(m_suspendRequested, ApplicationLifecycleState::Suspend);
            transitionByCondition(m_shutdownRequested, ApplicationLifecycleState::Shutdown);
            break;
        case ApplicationLifecycleState::Inactive:
            transitionByCondition(m_inputDetected, ApplicationLifecycleState::Active);
            transitionByCondition(m_shutdownRequested, ApplicationLifecycleState::Shutdown);
            transitionByCondition(m_suspendRequested, ApplicationLifecycleState::Suspend);
            break;
        case ApplicationLifecycleState::Suspend:
            transitionByCondition(m_shutdownRequested, ApplicationLifecycleState::Shutdown);
            break;
        case ApplicationLifecycleState::Shutdown:
            // Final state, no transition
            break;
    }
}

void ApplicationLifecycle::onEnterState(ApplicationLifecycleState state) {
    LOG(INFO) << "ApplicationLifecycle: " << stateToString(m_previousState) << " -> " << stateToString(state);
    m_pendingEvents.emplace_back(m_previousState, state);
}

void ApplicationLifecycle::onLeaveState(ApplicationLifecycleState state) {
    m_previousState = state;
}

void ApplicationLifecycle::clearFlags() {
    m_inputDetected = false;
    m_inactivityDetected = false;
    m_suspendRequested = false;
}

void ApplicationLifecycle::runInputWatcherLoop() {
    using namespace std::chrono_literals;

    std::vector<int> handles {openInputDeviceHandles()};
    std::size_t retryTick {0};

    while (!m_isStopping.load()) {
        if (handles.empty()) {
            std::this_thread::sleep_for(1s);
            ++retryTick;

            if (retryTick >= 5) {
                handles = openInputDeviceHandles();
                retryTick = 0;
            }

            evaluateInactivityTimeout();
            continue;
        }

        processInputHandles(handles);
        evaluateInactivityTimeout();
    }

    closeInputDeviceHandles(handles);
}

std::vector<int> ApplicationLifecycle::openInputDeviceHandles() const {
    std::vector<int> handles {};

    std::error_code error {};
    std::filesystem::path const inputPath {"/dev/input"};
    if (!std::filesystem::exists(inputPath, error) || error) {
        return handles;
    }

    for (std::filesystem::directory_entry const& entry : std::filesystem::directory_iterator(inputPath, error)) {
        if (error) {
            break;
        }

        if (!entry.is_character_file(error) || error) {
            continue;
        }

        std::string const fileName {entry.path().filename().string()};
        if (fileName.rfind("event", 0) != 0) {
            continue;
        }

        int const fd {::open(entry.path().c_str(), O_RDONLY | O_NONBLOCK)};
        if (fd >= 0) {
            handles.push_back(fd);
        }
    }

    return handles;
}

void ApplicationLifecycle::closeInputDeviceHandles(std::vector<int>& handles) const {
    for (int const fd : handles) {
        if (fd >= 0) {
            ::close(fd);
        }
    }
    handles.clear();
}

void ApplicationLifecycle::processInputHandles(std::vector<int> const& handles) {
    std::vector<pollfd> pollDescriptors {};
    pollDescriptors.reserve(handles.size());

    for (int const fd : handles) {
        pollfd descriptor {};
        descriptor.fd = fd;
        descriptor.events = POLLIN;
        pollDescriptors.push_back(descriptor);
    }

    int const pollResult {::poll(pollDescriptors.data(), static_cast<nfds_t>(pollDescriptors.size()), 1000)};
    if (pollResult <= 0) {
        return;
    }

    for (pollfd const& descriptor : pollDescriptors) {
        if ((descriptor.revents & POLLIN) == 0) {
            continue;
        }

        std::array<input_event, 16> events {};
        ssize_t const bytesRead {::read(descriptor.fd, events.data(), sizeof(events))};
        if (bytesRead <= 0) {
            continue;
        }

        std::size_t const eventCount {static_cast<std::size_t>(bytesRead) / sizeof(input_event)};
        for (std::size_t index {0}; index < eventCount; ++index) {
            input_event const& ev {events[index]};
            if (ev.type != EV_SYN) {
                notifyUserInput();
                break;
            }
        }
    }
}

void ApplicationLifecycle::evaluateInactivityTimeout() {
    bool shouldTransition {false};

    {
        std::lock_guard<std::mutex> const lock {m_mutex};

        if (currentState() != ApplicationLifecycleState::Active) {
            return;
        }

        auto const now {std::chrono::steady_clock::now()};
        auto const idleDuration {now - m_lastInputAt};
        if (idleDuration < m_inactivityTimeout) {
            return;
        }

        m_inactivityDetected = true;
        shouldTransition = true;
    }

    if (shouldTransition) {
        processStateMachine();
    }
}

void ApplicationLifecycle::processStateMachine() {
    std::vector<std::pair<ApplicationLifecycleState, ApplicationLifecycleState>> pendingEvents {};

    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        runStateMachine();
        pendingEvents = std::move(m_pendingEvents);
        m_pendingEvents.clear();
    }

    for (auto const& [previousState, currentState] : pendingEvents) {
        m_mediator.notify(ApplicationLifecycleStateChangedEvent {previousState, currentState});
    }
}

void ApplicationLifecycle::onApplicationStarted(ApplicationStartedEvent const&) {
    {
        std::lock_guard<std::mutex> const lock {m_mutex};
        m_applicationReady = true;
    }

    processStateMachine();
}

void ApplicationLifecycle::onApplicationClosed(ApplicationClosedEvent const&) {
    requestShutdown();
}
