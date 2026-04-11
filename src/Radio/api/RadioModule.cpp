#include "RadioModule.h"

#include <WidgetRegistratorIfc.h>

#include "ConfigurationRegistryIfc.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/RadioSettingsPageViewModel.h"

void RadioModule::registerExports(Injector& container) {
}

void RadioModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<RadioSettingsPageViewModel>(*this, "RadioSettingsPageViewModel");
}

void RadioModule::onInitialize() {
    auto widgetRegistrator = resolve<WidgetRegistratorIfc>();
    widgetRegistrator->registerWidget(WidgetMetadata("RadioCard", WidgetLayout("qrc:/qt/qml/Radio/qml/RadioCard.qml", 2, 1, 0, 3)));

    // Register Configuration page
    auto configRegistry = resolve<ConfigurationRegistryIfc>();
    configRegistry->registerProvider("radio-setting", ConfigurationMeta {"Connectivity", "Radio", "/qt/qml/Radio/qml/RadioSettings.qml"});
}