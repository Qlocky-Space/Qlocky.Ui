#ifndef QLOCKY_UI_ENGINE_IFC_H
#define QLOCKY_UI_ENGINE_IFC_H

#include <QString>

class QQmlApplicationEngine;

/**
 * A User Interface QML engine interface
 *
 * Bridge to QML related AppEngine
 */
class UiEngineIfc {
public:

    /**
     * Get the QML application engine
     */
    virtual QQmlApplicationEngine& getAppEngine() = 0;

    virtual ~UiEngineIfc() = default;
};

#endif