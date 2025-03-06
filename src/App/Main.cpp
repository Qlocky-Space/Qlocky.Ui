#include <boost/di.hpp>
#include <boost/di/extension/injector.hpp>
#include <QGuiApplication>

#include "api/ApplicationIfc.h"
#include "AppShellModule.h"
#include "internal/QlockyApp.h"
#include "ModuleIfc.h"
#include "QlockyConfig.h"
#include "UiEngineIfc.h"

namespace di = boost::di;

/**
 * Create and register and application in and with IoC container
 */
template<class T>
std::shared_ptr<T> createApplication(Injector& container) {
    container.install(di::bind<ApplicationIfc>().to<T>().in(di::singleton));

    return std::static_pointer_cast<T>(container.create<std::shared_ptr<ApplicationIfc>>());
}

int main(int argc, char* argv[]) {
    // Setup basic information for application
    auto coreApp {std::make_unique<QGuiApplication>(argc, argv)};
    coreApp->setApplicationName("QlockyApp");
    coreApp->setOrganizationName("Qlocky");
    coreApp->setOrganizationDomain("https://github.com/Qlocky-Space");
    coreApp->setApplicationVersion(QLOCKY_APP_VERSION);

    // Setup main application
    Injector globalContainer {di::make_injector()};
    auto app {createApplication<QlockyApp>(globalContainer)};
    app->addModule<AppShellModule>();

    app->perform(std::shared_ptr<Injector> {&globalContainer});

    // Provide an main application loop
    int const errorCode {coreApp->exec()};

    app->finish();

    return errorCode;
}
