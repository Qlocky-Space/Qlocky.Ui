declare_module(AppShell)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.h

    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.cpp
)

set(MODULE_QML_SRC
    qml/Main.qml
    qml/AppWindow.qml
    qml/WindowContent.qml
    qml/StatusBar.qml
)

set(MODULE_QML_RESOURCES
    resources/settings.png
    resources/signal.png
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Widget
)
setup_module()
