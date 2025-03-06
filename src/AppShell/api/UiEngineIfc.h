#ifndef QLOCKY_UI_ENGINE_IFC_H
#define QLOCKY_UI_ENGINE_IFC_H

#include <QString>

class QQmlApplicationEngine;

#define QLOCKY_QML_LIB_1_0 "QlockyUiLib", 1U, 0U

/**
 * TODO
 */
class UiEngineIfc {
public:

    virtual QQmlApplicationEngine& getAppEngine() = 0;

    virtual void addSourceImportPath(QString const& path) = 0;

    virtual ~UiEngineIfc() = default;
};

#endif