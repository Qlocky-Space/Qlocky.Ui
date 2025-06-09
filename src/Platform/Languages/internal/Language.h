#ifndef QLOCKY_LANGUAGE_H
#define QLOCKY_LANGUAGE_H

#include <map>
#include <QString>

/**
 * Struct represents a single language.
 * It is used to define the languages supported by the application.
 */
struct Language {

    Language(QString file, QString langCode, Qt::LayoutDirection dir = Qt::LayoutDirection::LeftToRight) :
        fileName {std::move(file)},
        code {std::move(langCode)},
        direction {dir} {
    }

    QString fileName;
    QString code;
    Qt::LayoutDirection direction;
};

#endif