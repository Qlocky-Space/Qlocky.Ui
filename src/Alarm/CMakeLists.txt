declare_module(Alarm)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/PingCommand.h

    ${CMAKE_CURRENT_LIST_DIR}/view/ClockCardViewModel.h
)

set(MODULE_QML_SRC
    qml/ClockCard.qml
)

set(MODULE_QML_RESOURCES
    resources/fonts/DS-DIGI.TTF
)

set(MODULE_LINK
    qlocky::Ui
)
setup_module()
