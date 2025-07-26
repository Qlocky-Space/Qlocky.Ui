#include "OsModule.h"

#include "internal/TimeProvider.h"
#include "NetworkDriverIfc.h"

// include platform specific drivers
#ifdef OS_IS_QLOCKY
#include "internal/qlocky/Nl80211Driver.h"
#else
#include "internal/mock/NetworkDriverStub.h"
#endif

void OsModule::registerExports(Injector& container) {
    container.install(boost::di::bind<TimeProviderIfc>().to<TimeProvider>());

#ifdef OS_IS_QLOCKY
    container.install(boost::di::bind<NetworkDriverIfc>().to<Nl80211Driver>());
#else
    container.install(boost::di::bind<NetworkDriverIfc>().to<NetworkDriverStub>());
#endif
}
