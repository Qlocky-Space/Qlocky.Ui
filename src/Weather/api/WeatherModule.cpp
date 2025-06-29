#include "WeatherModule.h"

#include <WidgetRegistratorIfc.h>

void WeatherModule::registerExports(Injector& container) {
}

void WeatherModule::onInitialize() {
    auto widgetRegistrator = resolve<WidgetRegistratorIfc>();

    widgetRegistrator->registerWidget(WidgetMetadata("WeatherCard", WidgetLayout("qrc:/qt/qml/Weather/qml/WeatherCard.qml", 0, 2, 0, 2)));
    widgetRegistrator->registerWidget(WidgetMetadata("WeatherPredictionCard", WidgetLayout("qrc:/qt/qml/Weather/qml/WeatherPredictionCard.qml", 2, 1, 0, 1)));
}
