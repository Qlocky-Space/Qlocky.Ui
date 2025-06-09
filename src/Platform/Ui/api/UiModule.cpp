#include "UiModule.h"

#include "internal/UiEngine.h"

void UiModule::registerExports(Injector& container) {
    container.install(boost::di::bind<UiEngineIfc>().to<UiEngine>());
}
