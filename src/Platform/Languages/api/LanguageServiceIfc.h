#ifndef QLOCKY_LANGUAGE_SERVICE_IFC_H
#define QLOCKY_LANGUAGE_SERVICE_IFC_H

#include "api/LanguageTypes.h"

class LanguageServiceIfc {
public:

    /**
     * This function is responsible for loading the language resources
     * and making them available for the application.
     * It should handle any necessary initialization or configuration
     * required to support the specified language.
     *
     * @param languageType The type of language to load.
     */
    virtual void loadLanguage(LanguageTypes languageType) = 0;

    virtual ~LanguageServiceIfc() = default;
};

#endif