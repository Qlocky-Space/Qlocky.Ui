#include "RestApiModule.h"

#include "internal/JsonRestFulApi.h"

void RestApiModule::registerExports(Injector& container) {
    container.install(boost::di::bind<RestApi>().to<JsonRestFulApi>());
}

void RestApiModule::registerQmlTypes() {
}

void RestApiModule::onInitialize() {
}