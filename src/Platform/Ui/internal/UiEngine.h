#ifndef QLOCKY_UI_ENGINE_H
#define QLOCKY_UI_ENGINE_H

#include <QQmlApplicationEngine>

#include "api/UiEngineIfc.h"

/**
 * @see UiEngineIfc
 */
class UiEngine final : public UiEngineIfc {
public:

    /**
     * @see UiEngineIfc::getAppEngine
     */
    QQmlApplicationEngine& getAppEngine() final {
        return m_engine;
    }

    /**
     * @see UiEngineIfc::installTranslator
     */
    bool installTranslator(QTranslator* messageFile) final;

    /**
     * @see UiEngineIfc::removeTranslator
     */
    bool removeTranslator(QTranslator* messageFile) final;

    /**
     * @see UiEngineIfc::registerImageProvider
     */
    void registerImageProvider(QString const& name, QQmlImageProviderBase* provider) final;

    /**
     * @see UiEngineIfc::setLayoutDirection
     */
    void setLayoutDirection(Qt::LayoutDirection direction) final;

    UiEngine() = default;
    ~UiEngine() final = default;

private:

    QQmlApplicationEngine m_engine {};
};

#endif