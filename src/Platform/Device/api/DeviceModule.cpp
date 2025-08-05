#include "DeviceModule.h"

#include "internal/DeviceInfoProvider.h"

void DeviceModule::registerExports(Injector& container) {
    container.install(boost::di::bind<DeviceInfoProviderIfc>().to<DeviceInfoProvider>());
}
