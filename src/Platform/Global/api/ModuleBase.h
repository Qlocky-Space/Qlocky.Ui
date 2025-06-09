#ifndef QLOCKY_MODULE_IFC_H
#define QLOCKY_MODULE_IFC_H

#include <boost/di.hpp>
#include <boost/di/extension/injector.hpp>

/**
 * Short hand for IoC injector for boost::di
 * @see also boost::di reference
 */
using Injector = boost::di::extension::injector<>;

/**
 * A module is a encapulation for a feature in the application.
 * This contains the UI and all it's required business logic.
 *
 * @see https://www.notion.so/qlocky/Qlocky-Ui-Design-Documentation-01e85d605d9145a1ba3d1b56f6972ba9?pvs=4#d608b9c6c30e4ee7ad7404c9fbdd3232
 */
class ModuleBase {
public:

    /**
     * Initialize the module. Must only be called once per module life time
     * @param container The application (parent) container
     */
    void initialize(Injector& container) {
        m_container = &container;

        registerExports(container);
        registerQmlTypes();

        onInitialize();
    }

    /**
     * Resolve a component in the container.
     * This includes also the application and other components.
     */
    template<class T>
    std::shared_ptr<T> resolve() {
        return m_container->create<std::shared_ptr<T>>();
    }

    ModuleBase() = default;
    virtual ~ModuleBase() = default;

protected:

    /**
     * Register all components which must be exported for other modules.
     * @param container the container where the compoents must be registered to.
     */
    virtual void registerExports(Injector& container) {
    }

    /**
     * Register all QML types and make it available in *.qml file.
     */
    virtual void registerQmlTypes() { };

    /**
     * This method is called after the module has been initialized.
     * It can be used to perform additional initialization steps.
     */
    virtual void onInitialize() { };

private:

    Injector* m_container {nullptr};
};

#endif