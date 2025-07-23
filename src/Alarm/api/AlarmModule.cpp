#include "AlarmModule.h"

#include <WidgetRegistratorIfc.h>

#include "Command/CommandRegistryUtil.h"
#include "commands/AlarmEditCommand.h"
#include "commands/AlarmNewCommand.h"
#include "commands/AlarmRemoveCommand.h"
#include "internal/AlarmOverlaySelector.h"
#include "internal/AlarmPreferencesRepository.h"
#include "internal/AlarmRepository.h"
#include "internal/AlarmService.h"
#include "Navigation/InteractiveUriRegistryIfc.h"
#include "QmlRegistryUtil.h"
#include "view/AlarmActiveDialogViewModel.h"
#include "view/AlarmDayUtils.h"
#include "view/AlarmDialogViewModel.h"
#include "view/AlarmListCardViewModel.h"
#include "view/AlarmListModel.h"
#include "view/ClockCardViewModel.h"
#include "view/DayOfWeekViewModel.h"
#include "view/TimeConverter.h"

void AlarmModule::registerExports(Injector& container) {
    container.install(boost::di::bind<AlarmServiceIfc>().to<AlarmService>());
    container.install(boost::di::bind<AlarmRepositoryIfc>().to<AlarmRepository>());
    container.install(boost::di::bind<AlarmPreferencesRepositoryIfc>().to<AlarmPreferencesRepository>());
    container.install(boost::di::bind<AlarmOverlaySelector>());
}

void AlarmModule::registerQmlTypes() {
    QmlRegistryUtil::qmlRegisterViewModel<ClockCardViewModel>(*this, "ClockCardViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<AlarmListCardViewModel>(*this, "AlarmListCardViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<AlarmDialogViewModel>(*this, "AlarmDialogViewModel");
    QmlRegistryUtil::qmlRegisterViewModel<AlarmActiveDialogViewModel>(*this, "AlarmActiveDialogViewModel");

    qmlRegisterSingletonInstance<TimeConverter>("Alarm", 1, 0, "TimeConverter", resolve<TimeConverter>().get());
    qmlRegisterSingletonInstance<AlarmDayUtils>("Alarm", 1, 0, "AlarmDayUtils", resolve<AlarmDayUtils>().get());
    qmlRegisterType<AlarmItemViewModel>("Alarm", 1, 0, "AlarmItemViewModel");
    qmlRegisterType<AlarmListModel>("Alarm", 1, 0, "AlarmListModel");

    qmlRegisterUncreatableType<DayOfWeekViewModel>("Alarm", 1, 0, "DayOfWeekViewModel", "DayOfWeekViewModel is uncreatable"
                                                                                        " because it is an enum class. Use DayOfWeekViewModel::Days instead.");
}

void AlarmModule::onInitialize() {
    auto widgetRegistrator = resolve<WidgetRegistratorIfc>();
    widgetRegistrator->registerWidget(WidgetMetadata("ClockCard", WidgetLayout("qrc:/qt/qml/Alarm/qml/ClockCard.qml", 0, 2, 0, 3)));
    widgetRegistrator->registerWidget(WidgetMetadata("AlarmListCard", WidgetLayout("qrc:/qt/qml/Alarm/qml/AlarmListCard.qml", 0, 3, 3, 2)));

    auto irRegistry = resolve<InteractiveUriRegistryIfc>();
    irRegistry->registerUri(Uri {"qlocky://alarmDialog"}, InteractiveMeta {InteractiveMeta::Type::Dialog, "/qt/qml/Alarm/qml/AlarmDialog.qml"});
    irRegistry->registerUri(Uri {"qlocky://alarmActiveDialog"}, InteractiveMeta {InteractiveMeta::Type::Dialog, "/qt/qml/Alarm/qml/AlarmActiveDialog.qml"});

    CommandRegistryUtil::registerCommand<AlarmEditCommand>(*this, "alarm-edit");
    CommandRegistryUtil::registerCommand<AlarmNewCommand>(*this, "alarm-new");
    CommandRegistryUtil::registerCommand<AlarmRemoveCommand>(*this, "alarm-remove");

    auto alarmService = resolve<AlarmServiceIfc>();
    alarmService->initialize();

    auto alarmRepository = resolve<AlarmRepositoryIfc>();
    alarmRepository->initialize();

    auto alarmSelector = resolve<AlarmOverlaySelector>();
    alarmSelector->initialize();
}