#ifndef SRC_DEVICE_VIEW_LIFECYCLE_STATE_TYPE_H
#define SRC_DEVICE_VIEW_LIFECYCLE_STATE_TYPE_H

#include <QObject>

/**
 * LifecycleStateType exposes ApplicationLifecycleState as a QML-accessible enumeration.
 */
class LifecycleStateType : public QObject {
    Q_OBJECT

public:

    enum class State {
        Startup,
        Active,
        Inactive,
        Suspend,
        Shutdown
    };
    Q_ENUM(State)
};

#endif // SRC_DEVICE_VIEW_LIFECYCLE_STATE_TYPE_H
