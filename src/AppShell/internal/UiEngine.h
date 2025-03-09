#ifndef QLOCKY_UI_ENGINE_H
#define QLOCKY_UI_ENGINE_H

#include <QQmlApplicationEngine>

#include "api/UiEngineIfc.h"

class UiEngine final : public UiEngineIfc {
public:

    UiEngine() = default;
    ~UiEngine() final = default;

    QQmlApplicationEngine& getAppEngine() final {
        return m_engine;
    }

private:

    QQmlApplicationEngine m_engine;
};

#endif