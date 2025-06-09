#ifndef QLOCKY_LANGUAGE_SERVICE_IFC_H
#define QLOCKY_LANGUAGE_SERVICE_IFC_H

#include "api/LanguageCode.h"

class LanguageServiceIfc {
public:

    /**
     * This function is responsible for loading the language resources
     * and making them available for the application.
     * It should handle any necessary initialization or configuration
     * required to support the specified language.
     *
     * @param language The type of language to load.
     */
    virtual void loadLanguage(LanguageCode language) = 0;

    virtual ~LanguageServiceIfc() = default;
};

#endif