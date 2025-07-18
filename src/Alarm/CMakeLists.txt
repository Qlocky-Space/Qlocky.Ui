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

    ${CMAKE_CURRENT_LIST_DIR}/internal/PingCommand.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmService.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmMapper.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmRepositoryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmRepository.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmPreferencesRepositoryIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmPreferencesRepository.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmPreferencesRepository.cpp

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
)

set(MODULE_QML_SRC
    qml/ClockCard.qml
    qml/AlarmDialog.qml
    qml/internal/AlarmList.qml
    qml/internal/AlarmListItem.qml
    qml/internal/AlarmSwipeButton.qml
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

    nlohmann_json::nlohmann_json
)

setup_module()
