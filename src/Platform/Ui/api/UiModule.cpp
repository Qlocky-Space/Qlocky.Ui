#include "UiModule.h"

#include "Command/CommandArgs.h"
#include "Command/CommandRegistryUtil.h"
#include "internal/CommandDispatcher.h"
#include "internal/CommandExecutor.h"
#include "internal/PageNavigator.h"
#include "internal/UiEngine.h"
#include "Navigation/NavigateBackCommand.h"
#include "Navigation/NavigateToPageCommand.h"
#include "Navigation/Uri.h"
#include "QmlRegistryUtil.h"

void UiModule::registerExports(Injector& container) {
    container.install(boost::di::bind<UiEngineIfc>().to<UiEngine>());
    container.install(boost::di::bind<NavigatorIfc>().to<PageNavigator>());
    container.install(boost::di::bind<CommandDispatcherIfc>().to<CommandDispatcher>());
    container.install(boost::di::bind<CommandExecutor>().to<CommandExecutor>());
}

void UiModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<CommandExecutor>(*this, "CommandExecutor");
}

void UiModule::onInitialize() {
    auto navigator = resolve<NavigatorIfc>();
    navigator->navigateToDefault();

    CommandRegistryUtil::registerCommand<NavigateBackCommand>(*this, "nav-back");
    CommandRegistryUtil::registerCommand<NavigateToPageCommand>(*this, "nav-to");
}