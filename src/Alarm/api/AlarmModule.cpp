#include "AlarmModule.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "internal/PingCommand.h"
#include "UiEngineIfc.h"
#include "view/ClockCardViewModel.h"

void AlarmModule::registerExports(Injector& container) {
    container.install(boost::di::bind<PingCommand>());
}

void AlarmModule::registerQmlTypes() {
    // qmlRegisterType<ClockCardViewModel>("Qlocky.Alarm", 1, 0, "ClockCardViewModel");
}

void AlarmModule::onInitialize() {
    QQmlApplicationEngine& uiEngine {resolve<UiEngineIfc>()->getAppEngine()};

    // TODO Works, but ClockCardViewModel is not global in QML. Maybe create a Factory class and register with qmlRegisterType?
    /*
     * QML:
     *
     * import Qlocky.Alarm 1.0
     *
     * AlarmModuleFactory {
     *    id: alarmModuleFactory
     * }
     *
     * property ClockCardViewModel clockCardViewModel: alarmModuleFactory.clockCardViewModel
     * [..]
     *     clockCardViewModel.pingCommand.execute()
     * [..]
     */
    uiEngine.rootContext()->setContextProperty("ClockCardViewModel", resolve<ClockCardViewModel>().get());
}