#include "AppShellModule.h"

#include "api/Mediator.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/MainPageViewModel.h"
#include "view/MainWindowViewModel.h"
#include "view/SettingPageViewModel.h"

void AppShellModule::registerExports(Injector& container) {
    container.install(boost::di::bind<Mediator>());
}

void AppShellModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<MainPageViewModel>(*this, "MainPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<SettingPageViewModel>(*this, "SettingPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<MainWindowViewModel>(*this, "MainWindowViewModel");
}

void AppShellModule::onInitialize() {
    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://main"}, InteractiveMeta {InteractiveMeta::Type::Page, "/qt/qml/AppShell/qml/MainPage.qml"});
    irRegistry->registerUri(Uri {"qlocky://settings"}, InteractiveMeta {InteractiveMeta::Type::Page, "/qt/qml/AppShell/qml/SettingPage.qml"});
}