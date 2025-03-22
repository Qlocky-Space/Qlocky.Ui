declare_module(Radio)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/RadioModule.h
)

set(MODULE_QML_SRC
    qml/RadioCard.qml
)

set(MODULE_QML_RESOURCES
    resources/play.png
    resources/skip.png
    resources/previous.png
)
setup_module()
