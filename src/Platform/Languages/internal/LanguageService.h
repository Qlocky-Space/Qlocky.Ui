#ifndef QLOCKY_LANGUAGE_SERVICE_H
#define QLOCKY_LANGUAGE_SERVICE_H

#include <QTranslator>
#include <set>

#include "api/LanguageServiceIfc.h"

class LanguageService final : public LanguageServiceIfc {
public:

    /**
     * @see LanguageServiceIfc::loadLanguage
     */
    void loadLanguage(LanguageTypes languageType) final;

private:

    QTranslator m_translator {};
};

#endif