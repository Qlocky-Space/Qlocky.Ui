#include <boost/di.hpp>
#include <boost/di/extension/injector.hpp>
#include <ng-log/logging.h>
#include <QGuiApplication>

#include "AlarmModule.h"
#include "api/ApplicationIfc.h"
#include "AppShellModule.h"
#include "ConfigurationModule.h"
#include "DeviceModule.h"
#include "internal/ConsoleSink.h"
#include "internal/QlockyApp.h"
#include "internal/QtLogForwarder.h"
#include "LanguageModule.h"
#include "NetworkModule.h"
#include "OsModule.h"
#include "PersistenceModule.h"
#include "QlockyConfig.h"
#include "RadioModule.h"
#include "RestApiModule.h"
#include "UiModule.h"

// required for boost container creation at compile time
namespace di = boost::di;

/**
 * Create and register and application in and with IoC container
 */
template<class T>
std::shared_ptr<T> createApplication(Injector& container) {
    container.install(di::bind<ApplicationIfc>().to<T>().in(boost::di::singleton));

    return std::static_pointer_cast<T>(container.create<std::shared_ptr<ApplicationIfc>>());
}

int main(int argc, char* argv[]) {
    using namespace std::chrono_literals;

    // https://doc.qt.io/archives/qt-5.15/qtvirtualkeyboard-deployment-guide.html#loading-the-plugin
    qputenv("QT_IM_MODULE", "qtvirtualkeyboard");
    qputenv("QT_VIRTUALKEYBOARD_STYLE", "qlocky");
    qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", ":/VirtualKeyboardResources/layouts");

    nglog::InitializeLogging(argv[0]);
    nglog::InstallFailureSignalHandler();
    nglog::EnableLogCleaner(24h * 30); // Clean logs older than 30 days
    QtLoggerForwarder::install();

    // Add the console sink for logging as early as possible
    auto consoleSink {std::make_shared<ConsoleSink>()};
    nglog::AddLogSink(consoleSink.get());

    // Setup basic information for application
    auto coreApp {std::make_unique<QGuiApplication>(argc, argv)};
    coreApp->setApplicationName("QlockyApp");
    coreApp->setOrganizationName("Qlocky");
    coreApp->setOrganizationDomain("https://github.com/Qlocky-Space");
    coreApp->setApplicationVersion(QLOCKY_APP_VERSION);

    // Setup main application
    Injector globalContainer {boost::di::make_injector()};
    auto app {createApplication<QlockyApp>(globalContainer)};
    // Register Platform modules
    app->addModule<OsModule>();
    app->addModule<PersistenceModule>();
    app->addModule<ConfigurationModule>();
    app->addModule<RestApiModule>();
    app->addModule<DeviceModule>();
    app->addModule<NetworkModule>();
    app->addModule<UiModule>();
    app->addModule<LanguageModule>();
    // Register modules
    app->addModule<AppShellModule>();
    app->addModule<AlarmModule>();
    app->addModule<RadioModule>();

    app->start(globalContainer);

    // Provide an main application loop
    int const errorCode {coreApp->exec()};

    app->finish();

    return errorCode;
}
