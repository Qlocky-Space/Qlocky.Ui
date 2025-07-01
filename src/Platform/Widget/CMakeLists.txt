declare_module(Widget)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/WidgetLoadedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/Widget.h
    ${CMAKE_CURRENT_LIST_DIR}/api/WidgetLoadedEvent.h
    ${CMAKE_CURRENT_LIST_DIR}/api/WidgetMetadata.h
    ${CMAKE_CURRENT_LIST_DIR}/api/WidgetRegistratorIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/WidgetModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/WidgetModule.cpp

    ${CMAKE_CURRENT_LIST_DIR}/internal/WidgetRegistrator.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/WidgetRegistrator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/WidgetLoader.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/WidgetLoader.cpp

)

set(MODULE_QML_SRC
    qml/Widget.qml
    qml/WidgetLayout.qml
)

setup_module()
