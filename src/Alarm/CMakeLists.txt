declare_module(Alarm)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmServiceIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/PingCommand.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmService.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/AlarmService.cpp

    ${CMAKE_CURRENT_LIST_DIR}/view/ClockCardViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/ClockCardViewModel.cpp
)

set(MODULE_QML_SRC
    qml/ClockCard.qml
)

set(MODULE_QML_RESOURCES
    resources/fonts/cour.ttf
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Widget
    qlocky::Os
)
setup_module()
