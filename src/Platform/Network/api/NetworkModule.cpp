#include "NetworkModule.h"

#include "internal/NetworkRepository.h"
#include "internal/NetworkService.h"

void NetworkModule::registerExports(Injector& container) {
    container.install(boost::di::bind<NetworkServiceIfc>().to<NetworkService>());
    container.install(boost::di::bind<NetworkRepositoryIfc>().to<NetworkRepository>());
}

void NetworkModule::onInitialize() {
    // Initialize the network repository
    auto networkRepository = resolve<NetworkRepositoryIfc>();
    networkRepository->initialize();

    // Initialize the network service
    auto networkService = resolve<NetworkServiceIfc>();
    networkService->initialize();
}