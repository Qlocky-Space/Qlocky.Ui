#ifndef QLOCKY_LANGUAGE_H
#define QLOCKY_LANGUAGE_H

#include <map>
#include <QString>

/**
 * Struct represents a single language.
 * It is used to define the languages supported by the application.
 */
struct Language {

    Language(QString file, QString langCode) :
        fileName {std::move(file)},
        code {std::move(langCode)} {
    }

    QString fileName;
    QString code;
};

#endif