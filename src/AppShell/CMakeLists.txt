declare_module(AppShell)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.h

    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.h

    ${CMAKE_CURRENT_LIST_DIR}/view/MainPageViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/MainPageViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/WidgetModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/WidgetModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/WidgetListModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/WidgetListModel.h

    ${CMAKE_CURRENT_LIST_DIR}/view/SettingPageViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/SettingPageViewModel.h
)

set(MODULE_QML_SRC
    qml/Main.qml
    qml/AppWindow.qml
    qml/MainPage.qml
    qml/SettingPage.qml
    qml/StatusBar.qml
)

set(MODULE_QML_RESOURCES
    resources/settings.png
    resources/signal.png
    resources/wallpaper-light.jpg
    resources/wallpaper-dark.png
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Widget
)
setup_module()
