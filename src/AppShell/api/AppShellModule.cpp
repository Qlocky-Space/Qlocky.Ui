#include "AppShellModule.h"

#include "api/Mediator.h"
#include "Command/CommandRegistryUtil.h"
#include "commands/ShowQrCodeCommand.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/MainPageViewModel.h"
#include "view/MainWindowViewModel.h"
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
}

void AppShellModule::onInitialize() {
    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://main"}, InteractiveMeta {InteractiveMeta::Type::Page, "/qt/qml/AppShell/qml/MainPage.qml"});
    irRegistry->registerUri(Uri {"qlocky://qr"}, InteractiveMeta {InteractiveMeta::Type::Dialog, "/qt/qml/AppShell/qml/QrDialog.qml"});

    CommandRegistryUtil::registerCommand<ShowQrCodeCommand>(*this, "show-qr-code");
}