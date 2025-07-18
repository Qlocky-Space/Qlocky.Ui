#include "PreferencesModule.h"

#include "internal/PreferencesService.h"

void PreferencesModule::registerExports(Injector& container) {
    container.install(boost::di::bind<PreferencesServiceIfc>().to<PreferencesService>());
}

void PreferencesModule::onInitialize() {
    auto preferences = resolve<PreferencesServiceIfc>();
    preferences->initialize();
}