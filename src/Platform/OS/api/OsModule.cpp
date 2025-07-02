#include "OsModule.h"

#include "internal/TimeService.h"

void OsModule::registerExports(Injector& container) {
    container.install(boost::di::bind<TimeServiceIfc>().to<TimeService>());
}
