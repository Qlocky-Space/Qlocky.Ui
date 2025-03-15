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
    qml/WidgetLayout.qml

    qml/Demo/WeatherCard.qml
    qml/Demo/WeatherPredictionCard.qml
    qml/Demo/ClockCard.qml
    qml/Demo/RadioCard.qml
)

set(MODULE_QML_RESOURCES
    resources/cloudy.png
    resources/cloudy-sun.png
    resources/cloudy-sun-rain.png
    resources/sun.png
    resources/snow.png
    resources/settings.png
    resources/signal.png

    resources/fonts/DS-DIGI.TTF
)
setup_module()
