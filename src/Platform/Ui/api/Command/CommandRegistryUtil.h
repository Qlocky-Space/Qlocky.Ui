#ifndef COMMAND_REGISTRY_UTIL_H
#define COMMAND_REGISTRY_UTIL_H

#include <string>

#include "api/ModuleBase.h"
#include "CommandDispatcherIfc.h"

/**
 * CommandRegistryUtil can be used to simplify command dispatcher registration
 */
class CommandRegistryUtil {
public:

    /**
     * Register a view model in the QML context.
     * This allows the view model to be used in QML files.
     * @tparam T The type of the view model to register.
     * @param module The module where the view model is registered.
     * @param name The name of the view model in the QML context.
     */
    template<class T>
    static void registerCommand(ModuleBase& module, CommandDispatcherIfc::CommandCode const& name) {
        auto dispatcher {module.resolve<CommandDispatcherIfc>()};

        std::shared_ptr<T> const command {module.resolve<T>()};
        dispatcher->reg(name, *command.get());
    }
};

#endif