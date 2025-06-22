declare_module(Widget)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/WidgetLoadedEvent.h

)

set(MODULE_QML_SRC
    qml/Card.qml
    qml/WidgetLayout.qml
)

setup_module()
