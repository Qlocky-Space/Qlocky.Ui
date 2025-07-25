#include "NetworkModule.h"

#include "internal/NetworkService.h"

void NetworkModule::registerExports(Injector& container) {
    container.install(boost::di::bind<NetworkServiceIfc>().to<NetworkService>());
}
