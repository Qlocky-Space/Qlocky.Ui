#ifndef WIDGET_REGISTRATOR_IFC_H
#define WIDGET_REGISTRATOR_IFC_H

#include "WidgetMetadata.h"

/**
 *
 */
class WidgetRegistratorIfc {
public:

    /**
     * Registers a widget with the system.
     *
     * This method is used to register a widget with the system, providing the necessary metadata
     * that describes the widget's properties, behavior, and how it should be instantiated.
     *
     * @param metadata The metadata describing the widget to be registered.
     */
    virtual void registerWidget(WidgetMetadata& metadata) = 0;

    virtual ~WidgetRegistratorIfc() = default;
};

#endif