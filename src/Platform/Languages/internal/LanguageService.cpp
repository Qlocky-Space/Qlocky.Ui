#include "LanguageService.h"

LanguageService::LanguageService(UiEngineIfc& uiEngine) :
    m_uiEngine {uiEngine} {
}

void LanguageService::loadLanguage(LanguageTypes languageType) {
    // TODO this is a temporary solution, the language files should be loaded from a configurable path
    QString const languageFilePath {"/workspaces/build/share/i18n"};

    QString languageFile {languageFilePath};

    switch (languageType) {
        case LanguageTypes::DE_CH:
            languageFile += "/QlockyApp_de.qm";
            break;
        case LanguageTypes::EN_US:
            languageFile += "/QlockyApp_en.qm";
            break;
        default:
            // Handle unsupported languages or set a default
            languageFile += "/QlockyApp_de.qm";
            break;
    }

    m_uiEngine.removeTranslator(&m_translator);

    if (m_translator.load(languageFile)) {
        m_uiEngine.installTranslator(&m_translator);
    }
    else {
        qWarning("Failed to load language file: %s", qPrintable(languageFile));
    }
}
