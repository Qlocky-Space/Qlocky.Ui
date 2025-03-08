#ifndef QLOCKY_APP_QLOCKYAPP_H
#define QLOCKY_APP_QLOCKYAPP_H

#include <memory>
#include <vector>

#include "api/ApplicationIfc.h"
#include "api/ModuleBase.h"

class QlockyApp : public ApplicationIfc {
public:

    QlockyApp();

    template<class T>
    void addModule() {
        static_assert(std::is_base_of_v<ModuleBase, T>, "Module does not inherit from ModuleBase");
        std::unique_ptr<T> module {std::make_unique<T>()};
        addModule(std::move(module));
    }

    void addModule(std::unique_ptr<ModuleBase> module);

    void perform(std::shared_ptr<Injector> container);
    void finish();

private:

    template<class T>
    std::shared_ptr<T> resolve();

    std::vector<std::unique_ptr<ModuleBase>> m_modules {};
    std::shared_ptr<Injector> m_container {};
};

#endif

template<class T>
inline std::shared_ptr<T> QlockyApp::resolve() {
    return m_container->create<std::shared_ptr<T>>();
}
