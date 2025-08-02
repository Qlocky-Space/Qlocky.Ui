#include "AppShellModule.h"

#include "api/Mediator.h"
#include "ConfigurationRegistryIfc.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/MainPageViewModel.h"
#include "view/MainWindowViewModel.h"
#include "view/NetworkStateType.h"
#include "view/StatusBarViewModel.h"
#include "view/VolumeType.h"

void AppShellModule::registerExports(Injector& container) {
    container.install(boost::di::bind<Mediator>());
}

void AppShellModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<MainPageViewModel>(*this, "MainPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<MainWindowViewModel>(*this, "MainWindowViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<StatusBarViewModel>(*this, "StatusBarViewModel");

    qmlRegisterUncreatableType<VolumeType>("AppShell", 1, 0, "VolumeType", "Cannot create VolumeType in QML");
    qmlRegisterUncreatableType<NetworkStateType>("AppShell", 1, 0, "NetworkStateType", "Cannot create NetworkStateType in QML");
}

void AppShellModule::onInitialize() {
    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://main"}, InteractiveMeta {InteractiveMeta::Type::Page, "/qt/qml/AppShell/qml/MainPage.qml"});

    auto configRegistry = resolve<ConfigurationRegistryIfc>();
    configRegistry->registerProvider("about", ConfigurationMeta {"System", "About", "/qt/qml/AppShell/qml/About.qml"});
    configRegistry->registerProvider("develop", ConfigurationMeta {"System", "Develop", "/qt/qml/AppShell/qml/Develop.qml"});
}