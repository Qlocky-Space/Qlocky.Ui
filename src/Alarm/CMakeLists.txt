declare_module(Alarm)

set(MODULE_QRC alarm.qrc)
set(MODULE_QML_IMPORT ${CMAKE_CURRENT_LIST_DIR}/qml)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AlarmModule.h
)

setup_module()
