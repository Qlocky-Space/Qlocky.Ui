#ifndef QLOCKY_LANGUAGE_SERVICE_H
#define QLOCKY_LANGUAGE_SERVICE_H

#include <QTranslator>
#include <set>

#include "Language.h"
#include "LanguageServiceIfc.h"
#include "UiEngineIfc.h"

class LanguageService final : public LanguageServiceIfc {
public:

    /**
     * Constructor for LanguageService.
     *
     * @param uiEngine Reference to the UI engine interface.
     */
    LanguageService(UiEngineIfc& uiEngine);

    /**
     * @see LanguageServiceIfc::loadLanguage
     */
    void loadLanguage(LanguageCode language) final;

private:

    void loadLanguage(Language const& language);

    using LanguageTypes = std::map<LanguageCode, Language>;

    static LanguageTypes const SupportedLanguages;

    QTranslator m_translator {};
    UiEngineIfc& m_uiEngine;
};

#endif