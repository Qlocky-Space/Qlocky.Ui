#ifndef SRC_DEVICE_VIEW_DEVELOP_VIEW_MODEL_H
#define SRC_DEVICE_VIEW_DEVELOP_VIEW_MODEL_H

#include <QObject>

#include "ApplicationLifecycleIfc.h"
#include "events/ApplicationLifecycleStateChangedEvent.h"
#include "LifecycleStateType.h"
#include "Mediator.h"

/**
 * ViewModel for the developer settings page.
 * Exposes the current application lifecycle state and notifies QML on transitions.
 */
class DevelopViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(LifecycleStateType::State lifecycleState READ lifecycleState NOTIFY lifecycleStateChanged)

public:

    explicit DevelopViewModel(Mediator& mediator, ApplicationLifecycleIfc& lifecycle);
    ~DevelopViewModel() final = default;

    /**
     * Returns the current lifecycle state.
     * @return The mapped LifecycleStateType::State value.
     */
    LifecycleStateType::State lifecycleState() const;

signals:

    void lifecycleStateChanged();

private:

    void onLifecycleStateChanged(ApplicationLifecycleStateChangedEvent const& event);

    ApplicationLifecycleIfc& m_lifecycle;
};

#endif // SRC_DEVICE_VIEW_DEVELOP_VIEW_MODEL_H
