#include "DevelopViewModel.h"

namespace {

LifecycleStateType::State toViewModelState(ApplicationLifecycleState state) {
    switch (state) {
        case ApplicationLifecycleState::Startup:
            return LifecycleStateType::State::Startup;
        case ApplicationLifecycleState::Active:
            return LifecycleStateType::State::Active;
        case ApplicationLifecycleState::Inactive:
            return LifecycleStateType::State::Inactive;
        case ApplicationLifecycleState::Suspend:
            return LifecycleStateType::State::Suspend;
        case ApplicationLifecycleState::Shutdown:
            return LifecycleStateType::State::Shutdown;
    }
    return LifecycleStateType::State::Startup;
}

} // namespace

DevelopViewModel::DevelopViewModel(Mediator& mediator, ApplicationLifecycleIfc& lifecycle) :
    QObject {nullptr},
    m_lifecycle {lifecycle} {
    mediator.subscribe<ApplicationLifecycleStateChangedEvent>(this, &DevelopViewModel::onLifecycleStateChanged);
}

LifecycleStateType::State DevelopViewModel::lifecycleState() const {
    return toViewModelState(m_lifecycle.state());
}

void DevelopViewModel::onLifecycleStateChanged(ApplicationLifecycleStateChangedEvent const&) {
    emit lifecycleStateChanged();
}
