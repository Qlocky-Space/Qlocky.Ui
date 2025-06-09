#include "UiEngine.h"

#include <QGuiApplication>

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

void UiEngine::setLayoutDirection(Qt::LayoutDirection direction) {
    qApp->setLayoutDirection(direction);
}
