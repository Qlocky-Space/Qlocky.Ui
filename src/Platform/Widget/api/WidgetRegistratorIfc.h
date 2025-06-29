#ifndef WIDGET_REGISTRATOR_IFC_H
#define WIDGET_REGISTRATOR_IFC_H

#include "WidgetMetadata.h"

/**
 * Used to register widgets within the system.
 *
 * This interface defines the contract for registering widgets, allowing the system to recognize
 * and manage widgets effectively.
 * Implementations of this interface should provide the logic for registering widgets based on
 * the provided metadata.
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
    virtual void registerWidget(WidgetMetadata const& metadata) = 0;

    virtual ~WidgetRegistratorIfc() = default;
};

#endif