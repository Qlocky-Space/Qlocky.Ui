#include "LanguageService.h"

#include <QDir>

LanguageService::LanguageTypes const LanguageService::SupportedLanguages {
    {LanguageCode::DE_CH, Language("QlockyApp_de.qm", "de_CH", Qt::LayoutDirection::LeftToRight)},
    {LanguageCode::EN_US, Language("QlockyApp_en.qm", "en_US", Qt::LayoutDirection::LeftToRight)},
};

LanguageService::LanguageService(UiEngineIfc& uiEngine) :
    m_uiEngine {uiEngine} {
}

void LanguageService::loadLanguage(LanguageCode language) {
    if (SupportedLanguages.find(language) == SupportedLanguages.end()) {
        qWarning("Unsupported language code: %d", static_cast<int>(language));
        return;
    }

    Language const& languageInfo = SupportedLanguages.at(language);
    loadLanguage(languageInfo);
}

void LanguageService::loadLanguage(Language const& language) {
    // TODO this is a temporary solution, the language files should be loaded from a configurable path
    QDir const languageFilePath {"/workspaces/build/share/i18n"};
    QFile const languageFile {languageFilePath.filePath(language.fileName)};

    m_uiEngine.removeTranslator(&m_translator);

    if (m_translator.load(languageFile.fileName())) {
        m_uiEngine.installTranslator(&m_translator);
    }
    else {
        qWarning("Failed to load language file: %s", qPrintable(languageFile.fileName()));
    }
}
