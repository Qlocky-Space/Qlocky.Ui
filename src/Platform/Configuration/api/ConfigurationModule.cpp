#include "ConfigurationModule.h"

#include "internal/ConfigurationRegistry.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/SettingPageViewModel.h"

void ConfigurationModule::registerExports(Injector& container) {
    container.install(boost::di::bind<ConfigurationRegistryIfc>().to<ConfigurationRegistry>());
}

void ConfigurationModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<SettingPageViewModel>(*this, "SettingPageViewModel");
}

void ConfigurationModule::onInitialize() {
    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://settings"}, InteractiveMeta {InteractiveMeta::Type::Page, "/qt/qml/Configuration/qml/SettingPage.qml"});
}
