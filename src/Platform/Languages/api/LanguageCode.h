#ifndef QLOCKY_LANGUAGE_CODES_H
#define QLOCKY_LANGUAGE_CODES_H

#include <map>
#include <QString>

/**
 * It is used to identify the languages supported by the application.
 * Each language code corresponds to a specific language and region.
 * The language codes are used to load the appropriate language resources.
 */
enum class LanguageCode {
    DE_CH, // German (Switzerland)
    EN_US, // English (United States)

    // Add more language codes as needed

    _, // Sentinel value to indicate the end of the enum
};

#endif