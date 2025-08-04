#include "UiModule.h"

#include "Command/CommandArgs.h"
#include "Command/CommandRegistryUtil.h"
#include "internal/CommandDispatcher.h"
#include "internal/CommandExecutor.h"
#include "internal/InteractiveNavigator.h"
#include "internal/InteractiveProvider.h"
#include "internal/InteractiveUriRegistry.h"
#include "internal/QrGenerator.h"
#include "internal/QrQuickImageProvider.h"
#include "internal/UiEngine.h"
#include "Navigation/NavigateToCommand.h"
#include "QmlRegistryUtil.h"

void UiModule::registerExports(Injector& container) {
    container.install(boost::di::bind<UiEngineIfc>().to<UiEngine>());
    container.install(boost::di::bind<InteractiveNavigatorIfc>().to<InteractiveNavigator>());
    container.install(boost::di::bind<CommandDispatcherIfc>().to<CommandDispatcher>());
    container.install(boost::di::bind<CommandExecutor>().to<CommandExecutor>());
    container.install(boost::di::bind<InteractiveProvider>().to<InteractiveProvider>());
    container.install(boost::di::bind<InteractiveUriRegistryIfc>().to<InteractiveUriRegistry>());
}

void UiModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<CommandExecutor>(*this, "CommandExecutor");
    QmlRegistryUtil::qmlRegisterViewModel<InteractiveProvider>(*this, "InteractiveProvider");
}

void UiModule::onInitialize() {
    // register commands
    CommandRegistryUtil::registerCommand<NavigateToCommand>(*this, "nav-to");

    auto engine = resolve<UiEngineIfc>();
    engine->registerImageProvider("qr", new QrQuickImageProvider());
}