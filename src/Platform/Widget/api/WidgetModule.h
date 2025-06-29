#ifndef QLOCKY_WIDGET_WIDGETMODULE_H
#define QLOCKY_WIDGET_WIDGETMODULE_H

#include "api/ModuleBase.h"

/**
 * AppShell module contains functionality for
 */
class WidgetModule final : public ModuleBase {
public:

    /**
     * @see ModuleBase::registerExports
     */
    void registerExports(Injector& container) final;

    WidgetModule() = default;
    ~WidgetModule() final = default;
};

#endif