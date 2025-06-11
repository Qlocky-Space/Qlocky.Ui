#ifndef QML_REGISTRY_UTIL_H
#define QML_REGISTRY_UTIL_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <string>

#include "api/ModuleBase.h"
#include "UiEngineIfc.h"

// required for qmlRegisterType
#include <QQmlEngine>

/**
 * QmlRegistryUtil is a utility class for registering QML types and view models in the QML context.
 */
class QmlRegistryUtil {
public:

    /**
     * Register a view model in the QML context.
     * This allows the view model to be used in QML files.
     * @tparam T The type of the view model to register.
     * @param module The module where the view model is registered.
     * @param name The name of the view model in the QML context.
     */
    template<class T>
    static void qmlRegisterViewModel(ModuleBase& module, std::string const& name) {
        QQmlApplicationEngine& uiEngine {module.resolve<UiEngineIfc>()->getAppEngine()};

        uiEngine.rootContext()->setContextProperty(name.c_str(), module.resolve<T>().get());
    }
};

#endif