declare_module(Alarm)

set(MODULE_QRC alarm.qrc)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.h
)

set(MODULE_QML_SRC
    qml/Alarm.qml
)

setup_module()
