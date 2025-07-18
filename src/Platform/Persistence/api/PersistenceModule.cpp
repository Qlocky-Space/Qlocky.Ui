#include "internal/PersistenceService.h"
#include "PersistenceModule.h"

void PersistenceModule::registerExports(Injector& container) {
    container.install(boost::di::bind<PersistenceServiceIfc>().to<PersistenceService>());
}

void PersistenceModule::onInitialize() {
    auto preferences = resolve<PersistenceServiceIfc>();
    preferences->initialize();
}