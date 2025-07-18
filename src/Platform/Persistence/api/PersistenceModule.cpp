#include "PersistenceModule.h"

#include "internal/PersistenceService.h"

void PersistenceModule::registerExports(Injector& container) {
    container.install(boost::di::bind<PersistenceServiceIfc>().to<PersistenceService>());
}

void PersistenceModule::onInitialize() {
    auto persistence = resolve<PersistenceServiceIfc>();
    persistence->initialize();
}