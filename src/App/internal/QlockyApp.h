#ifndef QLOCKY_APP_QLOCKYAPP_H
#define QLOCKY_APP_QLOCKYAPP_H

#include <memory>
#include <vector>

#include "api/ApplicationIfc.h"
#include "api/ModuleBase.h"

/**
 * The main application where all sub modules are registered.
 *
 * Contains the global container to resolve all registered components.
 */
class QlockyApp final : public ApplicationIfc {
public:

    /**
     * Register a module with template
     */
    template<class T>
    void addModule() {
        static_assert(std::is_base_of_v<ModuleBase, T>, "Module does not inherit from ModuleBase");
        std::unique_ptr<T> module {std::make_unique<T>()};
        addModule(std::move(module));
    }

    /**
     * Register a module with instance
     * @param module module base to register
     */
    void addModule(std::unique_ptr<ModuleBase> module);

    /**
     * Start the application.
     * @param container the global container
     */
    void start(Injector& container);

    /**
     * Cleanup the application before application ends
     */
    void finish();

    QlockyApp() = default;
    ~QlockyApp() final = default;

private:

    template<class T>
    std::shared_ptr<T> resolve() {
        assert(m_container != nullptr);
        return m_container->create<std::shared_ptr<T>>();
    }

    std::vector<std::unique_ptr<ModuleBase>> m_modules {};
    Injector* m_container {};
};

#endif
