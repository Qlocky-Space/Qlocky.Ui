#ifndef QLOCKY_MODULE_IFC_H
#define QLOCKY_MODULE_IFC_H

#include <boost/di.hpp>
#include <boost/di/extension/injector.hpp>

using Injector = boost::di::extension::injector<>;

class ModuleIfc {
public:

    void initialize(Injector& container) {
        m_container = &container;

        registerExports(container);
        registerQmlTypes();
    }

    template<class T>
    std::shared_ptr<T> resolve() {
        return m_container->create<std::shared_ptr<T>>();
    }

    virtual ~ModuleIfc() = default;

protected:

    virtual void registerExports(Injector& container) = 0;

    virtual void registerQmlTypes() = 0;

private:

    Injector* m_container {nullptr};
};

#endif