#include "RadioModule.h"

#include <WidgetRegistratorIfc.h>

void RadioModule::registerExports(Injector& container) {
}

void RadioModule::onInitialize() {
    auto widgetRegistrator = resolve<WidgetRegistratorIfc>();

    widgetRegistrator->registerWidget(WidgetMetadata("RadioCard", WidgetLayout("qrc:/qt/qml/Radio/qml/RadioCard.qml", 2, 1, 0, 3)));
}