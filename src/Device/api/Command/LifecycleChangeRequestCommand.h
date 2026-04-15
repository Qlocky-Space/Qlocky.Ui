#ifndef SRC_PLATFORM_OS_API_COMMANDS_LIFECYCLE_CHANGE_REQUEST_COMMAND_H
#define SRC_PLATFORM_OS_API_COMMANDS_LIFECYCLE_CHANGE_REQUEST_COMMAND_H

#include <Command/QmlCommandBase.h>

#include "ApplicationLifecycleIfc.h"

/**
 * Command to request a lifecycle state transition.
 */
class LifecycleChangeRequestCommand final : public QmlCommandBase {
public:

    /**
     * @param lifecycle Lifecycle service used to request state changes.
     */
    explicit LifecycleChangeRequestCommand(ApplicationLifecycleIfc& lifecycle);

protected:

    /**
     * @see CommandIfc::doExecute
     */
    void doExecute(CommandArgs const& data) final;

private:

    ApplicationLifecycleIfc& m_lifecycle;
};

#endif // SRC_PLATFORM_OS_API_COMMANDS_LIFECYCLE_CHANGE_REQUEST_COMMAND_H