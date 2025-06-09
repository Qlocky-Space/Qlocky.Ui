#include "LanguageService.h"

#include "QCoreApplication"
#include "QLocale"
#include "QTranslator"

void LanguageService::loadLanguage(LanguageTypes languageType) {
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

    qApp->removeTranslator(&m_translator);

    if (m_translator.load(languageFile)) {
        qApp->installTranslator(&m_translator);
    }
    else {
        qWarning("Failed to load language file: %s", qPrintable(languageFile));
    }
}
