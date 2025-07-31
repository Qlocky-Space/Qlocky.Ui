#include "AppShellModule.h"

#include "api/Mediator.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/MainPageViewModel.h"
#include "view/MainWindowViewModel.h"
#include "view/NetworkStateType.h"
#include "view/SettingPageViewModel.h"
#include "view/StatusBarViewModel.h"
#include "view/VolumeType.h"

void AppShellModule::registerExports(Injector& container) {
    container.install(boost::di::bind<Mediator>());
}

void AppShellModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<MainPageViewModel>(*this, "MainPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<SettingPageViewModel>(*this, "SettingPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<MainWindowViewModel>(*this, "MainWindowViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<StatusBarViewModel>(*this, "StatusBarViewModel");

    qmlRegisterUncreatableType<VolumeType>("AppShell", 1, 0, "VolumeType", "Cannot create VolumeType in QML");
    qmlRegisterUncreatableType<NetworkStateType>("AppShell", 1, 0, "NetworkStateType", "Cannot create NetworkStateType in QML");
}

void AppShellModule::onInitialize() {
    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://main"}, InteractiveMeta {InteractiveMeta::Type::Page, "/qt/qml/AppShell/qml/MainPage.qml"});
    irRegistry->registerUri(Uri {"qlocky://settings"}, InteractiveMeta {InteractiveMeta::Type::Page, "/qt/qml/AppShell/qml/SettingPage.qml"});
}