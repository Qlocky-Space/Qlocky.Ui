#ifndef QLOCKY_UI_ENGINE_IFC_H
#define QLOCKY_UI_ENGINE_IFC_H

#include <QString>

class QQmlApplicationEngine;
class QTranslator;

/**
 * UiEngineIfc is an interface for the UI engine that provides methods to manage the QML application engine,
 * install and remove translators, and access the application engine.
 * This interface is used to abstract the UI engine functionality, allowing for easier testing and modularity.
 */
class UiEngineIfc {
public:

    /**
     * This method is used to access the QML engine for loading QML files, managing contexts, etc.
     * @return Reference to the QQmlApplicationEngine instance.
     */
    virtual QQmlApplicationEngine& getAppEngine() = 0;

    /**
     * Installs a translator for the application.
     * @param messageFile The translator to install.
     * @return true if the translator was successfully installed, false otherwise.
     * @note This method is used to change the application's language at runtime.
     * @note The application must support translations for this to work.
     */
    virtual bool installTranslator(QTranslator* messageFile) = 0;

    /**
     * Removes a translator from the application.
     * @param messageFile The translator to remove.
     * @return true if the translator was successfully removed, false otherwise.
     * @note This method is used to revert the application's language changes.
     */
    virtual bool removeTranslator(QTranslator* messageFile) = 0;

    /**
     * Sets the layout direction for the application.
     * @param direction The layout direction to set (LeftToRight, RightToLeft, or LayoutDirectionAuto).
     */
    virtual void setLayoutDirection(Qt::LayoutDirection direction) = 0;

    virtual ~UiEngineIfc() = default;
};

#endif