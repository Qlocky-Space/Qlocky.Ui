#include "LanguageModule.h"

#include "api/LanguageTypes.h"
#include "internal/LanguageService.h"

void LanguageModule::registerExports(Injector& container) {
    container.install(boost::di::bind<LanguageServiceIfc>().to<LanguageService>());
}

void LanguageModule::onInitialize() {
    auto languageService {resolve<LanguageServiceIfc>()};

    // For now, we use DE_CH as the default language, could be based on user preferences in future
    languageService->loadLanguage(LanguageTypes::DE_CH);
}
