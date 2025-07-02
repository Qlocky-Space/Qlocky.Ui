#include "OsModule.h"

#include "internal/TimeProvider.h"

void OsModule::registerExports(Injector& container) {
    container.install(boost::di::bind<TimeProviderIfc>().to<TimeProvider>());
}
