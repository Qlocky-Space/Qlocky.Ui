declare_module(AppShell)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/AppShellModule.h

    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/MainWindowViewModel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/StatusBarViewModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/StatusBarViewModel.h

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
    qml/internal/QNetworkIcon.qml
    qml/internal/HomeIndicator.qml
    qml/Main.qml
    qml/AppWindow.qml
    qml/MainPage.qml
    qml/SettingPage.qml
    qml/StatusBar.qml
    qml/StatusBarOverlay.qml
    qml/StatusBarContent.qml
)

set(MODULE_QML_RESOURCES
    resources/wallpaper-light.jpg
    resources/wallpaper-dark.png
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Widget
)
setup_module()
