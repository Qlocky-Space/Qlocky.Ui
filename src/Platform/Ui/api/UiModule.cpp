#include "UiModule.h"

#include "Command/CommandArgs.h"
#include "internal/PageNavigator.h"
#include "internal/UiEngine.h"

void UiModule::registerExports(Injector& container) {
    container.install(boost::di::bind<UiEngineIfc>().to<UiEngine>());
    container.install(boost::di::bind<NavigatorIfc>().to<PageNavigator>());
}

void UiModule::registerQmlTypes() {
    qmlRegisterType<CommandArgs>("Ui", 1, 0, "CommandArgs");
}

void UiModule::onInitialize() {
    auto navigator = resolve<NavigatorIfc>();
    navigator->navigateToDefault();
}