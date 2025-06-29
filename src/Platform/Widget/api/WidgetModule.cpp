#include "WidgetModule.h"

#include "internal/WidgetLoader.h"
#include "internal/WidgetRegistrator.h"

void WidgetModule::registerExports(Injector& container) {
    container.install(boost::di::bind<WidgetLoaderIfc>().to<WidgetLoader>());
    container.install(boost::di::bind<WidgetRegistratorIfc>().to<WidgetRegistrator>());
}
