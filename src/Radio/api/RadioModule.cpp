#include "RadioModule.h"

#include <WidgetRegistratorIfc.h>

#include "ConfigurationRegistryIfc.h"
#include "internal/RadioBrowserStationProvider.h"
#include "internal/StationRepository.h"
#include "internal/StationService.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "StationRepositoryIfc.h"
#include "StationServiceIfc.h"
#include "view/RadioSettingsPageViewModel.h"
#include "view/RadioSourceSelectDialogViewModel.h"

void RadioModule::registerExports(Injector& container) {
    container.install(boost::di::bind<StationRepositoryIfc>().to<StationRepository>());
    container.install(boost::di::bind<StationServiceIfc>().to<StationService>());
}

void RadioModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<RadioSettingsPageViewModel>(*this, "RadioSettingsPageViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<RadioSourceSelectDialogViewModel>(*this, "RadioSourceSelectDialogViewModel");
}

void RadioModule::onInitialize() {
    auto stationRepository = resolve<StationRepositoryIfc>();
    stationRepository->initialize();

    auto stationService = resolve<StationServiceIfc>();
    stationService->registerProvider(resolve<RadioBrowserStationProvider>());

    auto widgetRegistrator = resolve<WidgetRegistratorIfc>();
    widgetRegistrator->registerWidget(WidgetMetadata("RadioCard", WidgetLayout("qrc:/qt/qml/Radio/qml/RadioCard.qml", 2, 1, 0, 3)));

    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://radioSourceSelectDialog"}, InteractiveMeta {InteractiveMeta::Type::Dialog, "/qt/qml/Radio/qml/RadioSourceSelectDialog.qml"});

    // Register Configuration page
    auto configRegistry = resolve<ConfigurationRegistryIfc>();
    configRegistry->registerProvider("radio-setting", ConfigurationMeta {"Connectivity", "Radio", "/qt/qml/Radio/qml/RadioSettings.qml"});
}