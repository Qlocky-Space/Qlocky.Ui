#include "DeviceModule.h"

#include "ConfigurationRegistryIfc.h"
#include "internal/DeviceInfoProvider.h"
#include "QmlRegistryUtil.h"
#include "view/AboutViewModel.h"

void DeviceModule::registerExports(Injector& container) {
    container.install(boost::di::bind<DeviceInfoProviderIfc>().to<DeviceInfoProvider>());
}

void DeviceModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<AboutViewModel>(*this, "AboutViewModel");
}

void DeviceModule::onInitialize() {
    // Initialize the device info provider
    auto deviceInfoProvider = resolve<DeviceInfoProviderIfc>();
    deviceInfoProvider->initialize();

    auto configRegistry = resolve<ConfigurationRegistryIfc>();
    configRegistry->registerProvider("about", ConfigurationMeta {"System", "About", "/qt/qml/Device/qml/About.qml"});
    configRegistry->registerProvider("develop", ConfigurationMeta {"System", "Develop", "/qt/qml/Device/qml/Develop.qml"});
}