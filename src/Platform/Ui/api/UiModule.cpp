#include "UiModule.h"

#include "internal/PageNavigator.h"
#include "internal/UiEngine.h"

void UiModule::registerExports(Injector& container) {
    container.install(boost::di::bind<UiEngineIfc>().to<UiEngine>());
    container.install(boost::di::bind<NavigatorIfc>().to<PageNavigator>());
}
