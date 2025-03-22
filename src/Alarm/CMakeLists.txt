declare_module(Alarm)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.h
)

set(MODULE_QML_SRC
    qml/ClockCard.qml
)

set(MODULE_QML_RESOURCES
    resources/fonts/DS-DIGI.TTF
)
setup_module()
