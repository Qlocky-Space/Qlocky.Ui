#include "NetworkModule.h"

#include "Command/CommandRegistryUtil.h"
#include "commands/NetworkConnectToCommand.h"
#include "commands/NetworkDisconnectCommand.h"
#include "commands/NetworkForgetCommand.h"
#include "ConfigurationRegistryIfc.h"
#include "internal/NetworkRepository.h"
#include "internal/NetworkService.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "NetworkStateType.h"
#include "QmlRegistryUtil.h"
#include "view/WiFiProfileDialogViewModel.h"
#include "view/WiFiSettingsPageViewModel.h"

void NetworkModule::registerExports(Injector& container) {
    container.install(boost::di::bind<NetworkServiceIfc>().to<NetworkService>());
    container.install(boost::di::bind<NetworkRepositoryIfc>().to<NetworkRepository>());
}

void NetworkModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<WiFiSettingsPageViewModel>(*this, "WiFiSettingsPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<WiFiProfileDialogViewModel>(*this, "WiFiProfileDialogViewModel");

    qmlRegisterUncreatableType<NetworkStateType>("Network", 1, 0, "NetworkStateType", "Cannot create NetworkStateType in QML");
}

void NetworkModule::onInitialize() {
    // Initialize the network repository
    auto networkRepository = resolve<NetworkRepositoryIfc>();
    networkRepository->initialize();

    // Initialize the network service
    auto networkService = resolve<NetworkServiceIfc>();
    networkService->initialize();

    // Register Commands
    CommandRegistryUtil::registerCommand<NetworkConnectToCommand>(*this, "network-connect");
    CommandRegistryUtil::registerCommand<NetworkDisconnectCommand>(*this, "network-disconnect");
    CommandRegistryUtil::registerCommand<NetworkForgetCommand>(*this, "network-forget");

    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://networkProfile"}, InteractiveMeta {InteractiveMeta::Type::Dialog, "/qt/qml/Network/qml/WiFiProfileDialog.qml"});

    // Register Configuration page
    auto configRegistry = resolve<ConfigurationRegistryIfc>();
    configRegistry->registerProvider("wifi-setting", ConfigurationMeta {"Connectivity", "Wi-Fi Settings", "/qt/qml/Network/qml/WiFiSettings.qml"});
}