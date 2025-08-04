#include "OsModule.h"

#include "internal/DeviceInfoProvider.h"
#include "internal/TimeProvider.h"
#include "NetworkDriverIfc.h"

// include platform specific drivers
#ifdef OS_IS_QLOCKY
#include "internal/qlocky/WpaSupplicantDBusDriver.h"
#else
#include "internal/mock/NetworkDriverStub.h"
#endif

void OsModule::registerExports(Injector& container) {
    container.install(boost::di::bind<TimeProviderIfc>().to<TimeProvider>());
    container.install(boost::di::bind<DeviceInfoProviderIfc>().to<DeviceInfoProvider>());

#ifdef OS_IS_QLOCKY
    container.install(boost::di::bind<NetworkDriverIfc>().to<WpaSupplicantDBusDriver>());
#else
    container.install(boost::di::bind<NetworkDriverIfc>().to<NetworkDriverStub>());
#endif
}
