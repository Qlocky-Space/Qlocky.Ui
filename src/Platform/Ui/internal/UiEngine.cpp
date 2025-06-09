#include "UiEngine.h"

#include <QCoreApplication>

bool UiEngine::installTranslator(QTranslator* messageFile) {
    if (messageFile) {
        qApp->installTranslator(messageFile);
        return true;
    }
    return false;
}

bool UiEngine::removeTranslator(QTranslator* messageFile) {
    if (messageFile) {
        qApp->removeTranslator(messageFile);
        return true;
    }
    return false;
}
