#include "NetworkModule.h"

#include "ConfigurationRegistryIfc.h"
#include "internal/NetworkRepository.h"
#include "internal/NetworkService.h"
#include "QmlRegistryUtil.h"
#include "view/WiFiSettingsPageViewModel.h"

void NetworkModule::registerExports(Injector& container) {
    container.install(boost::di::bind<NetworkServiceIfc>().to<NetworkService>());
    container.install(boost::di::bind<NetworkRepositoryIfc>().to<NetworkRepository>());
}

void NetworkModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<WiFiSettingsPageViewModel>(*this, "WiFiSettingsPageViewModel");
}

void NetworkModule::onInitialize() {
    // Initialize the network repository
    auto networkRepository = resolve<NetworkRepositoryIfc>();
    networkRepository->initialize();

    // Initialize the network service
    auto networkService = resolve<NetworkServiceIfc>();
    networkService->initialize();

    // Register Configuration page
    auto configRegistry = resolve<ConfigurationRegistryIfc>();
    configRegistry->registerProvider("wifi-setting", ConfigurationMeta {"Connectivity", "Wi-Fi Settings", "/qt/qml/Network/qml/WiFiSettings.qml"});
}