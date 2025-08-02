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

    ${CMAKE_CURRENT_LIST_DIR}/view/NetworkStateType.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/NetworkStateType.h
    ${CMAKE_CURRENT_LIST_DIR}/view/VolumeType.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/VolumeType.h
)

set(MODULE_QML_SRC
    qml/internal/QStatusBarAction.qml
    qml/internal/QStatusBarIcon.qml
    qml/internal/QStatusBarGroup.qml
    qml/internal/QStatusBarSlider.qml
    qml/internal/QStatusBarSliderWithButton.qml
    qml/internal/QStatusBarOverlay.qml
    qml/internal/QStatusBarContent.qml
    qml/internal/QHomeIndicator.qml
    qml/internal/IconUtil.qml
    qml/Main.qml
    qml/AppWindow.qml
    qml/MainPage.qml
    qml/StatusBar.qml
    qml/About.qml
    qml/Develop.qml
)

set_source_files_properties(qml/internal/IconUtil.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

set(MODULE_QML_RESOURCES
    resources/wallpaper-light.jpg
    resources/wallpaper-dark.png
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Widget
    qlocky::Network
    qlocky::Configuration
)
setup_module()
