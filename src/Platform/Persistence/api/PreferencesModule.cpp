#include "PreferencesModule.h"

#include "internal/PersistenceService.h"

void PreferencesModule::registerExports(Injector& container) {
    container.install(boost::di::bind<PersistenceServiceIfc>().to<PersistenceService>());
}

void PreferencesModule::onInitialize() {
    auto preferences = resolve<PersistenceServiceIfc>();
    preferences->initialize();
}