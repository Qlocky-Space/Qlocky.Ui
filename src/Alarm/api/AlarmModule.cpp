#include "AlarmModule.h"

#include <WidgetRegistratorIfc.h>

#include "internal/AlarmService.h"
#include "internal/PingCommand.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/ClockCardViewModel.h"

void AlarmModule::registerExports(Injector& container) {
    container.install(boost::di::bind<PingCommand>());
    container.install(boost::di::bind<AlarmServiceIfc>().to<AlarmService>());
}

void AlarmModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<ClockCardViewModel>(*this, "ClockCardViewModel");
}

void AlarmModule::onInitialize() {
    auto widgetRegistrator = resolve<WidgetRegistratorIfc>();
    widgetRegistrator->registerWidget(WidgetMetadata("ClockCard", WidgetLayout("qrc:/qt/qml/Alarm/qml/ClockCard.qml", 0, 2, 0, 3)));

    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://newAlarmDialog"}, InteractiveMeta {InteractiveMeta::Type::Dialog, "/qt/qml/Alarm/qml/NewAlarmDialog.qml"});

    auto alarmService = resolve<AlarmServiceIfc>();
    alarmService->initialize();
}