#include "LanguageModule.h"

#include "api/LanguageCode.h"
#include "internal/LanguageService.h"

void LanguageModule::registerExports(Injector& container) {
    container.install(boost::di::bind<LanguageServiceIfc>().to<LanguageService>());
}

void LanguageModule::onInitialize() {
    auto languageService {resolve<LanguageServiceIfc>()};

    // For now, we use DE_CH as the default language, could be based on user preferences in future
    languageService->loadLanguage(LanguageCode::DE_CH);
}
