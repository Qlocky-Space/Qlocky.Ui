declare_module(AppShell)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.h
    ${CMAKE_CURRENT_LIST_DIR}/api/MainWindowIfc.h
    ${CMAKE_CURRENT_LIST_DIR}/api/UiEngineIfc.h

    ${CMAKE_CURRENT_LIST_DIR}/internal/MainWindow.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/MainWindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/UiEngine.cpp

    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.cpp
)

set(MODULE_QML_SRC
    qml/AppWindow.qml
    qml/WindowContent.qml
    qml/StatusBar.qml
    qml/Card.qml
)

setup_module()
