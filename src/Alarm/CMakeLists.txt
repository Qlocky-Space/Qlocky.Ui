declare_module(Alarm)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmServiceIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmEntity.h
    ${CMAKE_CURRENT_LIST_DIR}/api/commands/AlarmNewCommand.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/commands/AlarmEditCommand.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/commands/AlarmRemoveCommand.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/events/AlarmAddedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/AlarmUpdatedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/AlarmRemovedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/events/AlarmActivatedEvent.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmMapper.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmRepositoryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmRepository.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmOverlaySelector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmOverlaySelector.h

    ${CMAKE_CURRENT_LIST_DIR}/view/ClockCardViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/ClockCardViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmListCardViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmListCardViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmItemViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmItemViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmListModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmListModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmDialogViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmDialogViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmActiveDialogViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmActiveDialogViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmMusicSourceViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmMusicSourceViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/TimeConverter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/TimeConverter.h
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmDayUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/AlarmDayUtils.h
    ${CMAKE_CURRENT_LIST_DIR}/view/DayOfWeekViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/DayOfWeekViewModel.h
)

set(MODULE_QML_SRC
    qml/ClockCard.qml
    qml/AlarmDialog.qml
    qml/AlarmActiveDialog.qml
    qml/internal/AlarmList.qml
    qml/internal/AlarmListItem.qml
    qml/internal/AlarmSwipeButton.qml
    qml/internal/AlarmDialogRepeated.qml
    qml/internal/AlarmDialogMusicSource.qml
    qml/internal/AlarmDialogNavigateTrailing.qml
    qml/internal/AlarmDialogMain.qml
    qml/internal/AlarmDialogProperty.qml
    qml/AlarmListCard.qml
)

set(MODULE_QML_RESOURCES
    resources/fonts/cour.ttf
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Persistence
    qlocky::Widget
    qlocky::Os
    qlocky::Device
    qlocky::Radio

    nlohmann_json::nlohmann_json
)

setup_module()
