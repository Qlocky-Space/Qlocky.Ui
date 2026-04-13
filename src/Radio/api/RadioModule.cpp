#include "RadioModule.h"

#include <WidgetRegistratorIfc.h>

#include "ConfigurationRegistryIfc.h"
#include "internal/RadioBrowserProvider.h"
#include "internal/RadioPlayer.h"
#include "internal/RadioRepository.h"
#include "internal/RadioService.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "RadioPlayerIfc.h"
#include "RadioRepositoryIfc.h"
#include "RadioServiceIfc.h"
#include "view/RadioCardViewModel.h"
#include "view/RadioSettingsPageViewModel.h"
#include "view/RadioSourceSelectDialogViewModel.h"

void RadioModule::registerExports(Injector& container) {
    container.install(boost::di::bind<RadioRepositoryIfc>().to<RadioRepository>());
    container.install(boost::di::bind<RadioServiceIfc>().to<RadioService>());
    container.install(boost::di::bind<RadioPlayerIfc>().to<RadioPlayer>());
}

void RadioModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<RadioCardViewModel>(*this, "RadioCardViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<RadioSettingsPageViewModel>(*this, "RadioSettingsPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<RadioSourceSelectDialogViewModel>(*this, "RadioSourceSelectDialogViewModel");
}

void RadioModule::onInitialize() {
    auto radioRepository = resolve<RadioRepositoryIfc>();
    radioRepository->initialize();

    auto radioService = resolve<RadioServiceIfc>();
    radioService->registerProvider(resolve<RadioBrowserProvider>());
    radioService->initialize();

    auto radioPlayer = resolve<RadioPlayerIfc>();
    radioPlayer->initialize();

    auto widgetRegistrator = resolve<WidgetRegistratorIfc>();
    widgetRegistrator->registerWidget(WidgetMetadata("RadioCard", WidgetLayout("qrc:/qt/qml/Radio/qml/RadioCard.qml", 2, 1, 0, 3)));

    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://radioSourceSelectDialog"}, InteractiveMeta {InteractiveMeta::Type::Dialog, "/qt/qml/Radio/qml/RadioSourceSelectDialog.qml"});

    // Register Configuration page
    auto configRegistry = resolve<ConfigurationRegistryIfc>();
    configRegistry->registerProvider("radio-setting", ConfigurationMeta {"Connectivity", "Radio", "/qt/qml/Radio/qml/RadioSettings.qml"});
}