declare_module(Weather)

set(MODULE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/api/WeatherModule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/api/WeatherModule.h
)

set(MODULE_QML_SRC
    qml/WeatherCard.qml
    qml/WeatherPredictionCard.qml
)

set(MODULE_QML_RESOURCES
    resources/cloudy.png
    resources/cloudy-sun.png
    resources/cloudy-sun-rain.png
    resources/sun.png
    resources/snow.png
)

set(MODULE_LINK
    qlocky::Ui
    qlocky::Widget
)

setup_module()
