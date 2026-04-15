#ifndef PLATFORM_WIDGET_API_WIDGETLOADERIFC_H
#define PLATFORM_WIDGET_API_WIDGETLOADERIFC_H

#include "WidgetMetadata.h"

/**
 * Interface for loading widgets into the application.
 * Implementations are responsible for creating, initializing, and managing widget lifecycles.
 */
class WidgetLoaderIfc {
public:

    /**
     * Loads a widget based on the provided metadata.
     * Implementations should create an instance of the widget and initialize it with
     * the specified layout and properties.
     *
     * @param metadata The metadata describing the widget to be loaded.
     */
    virtual void loadWidget(WidgetMetadata const& metadata) = 0;

    virtual ~WidgetLoaderIfc() = default;
};

#endif