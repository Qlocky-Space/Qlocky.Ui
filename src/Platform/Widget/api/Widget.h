#ifndef WIDGET_H
#define WIDGET_H

#include "WidgetMetadata.h"

/**
 * Represents a widget in the application.
 * It represents the loaded instances of the widget.
 */
class Widget {
public:

    Widget(WidgetMetadata const& metadata) :
        m_metadata(metadata) {
    }

    WidgetMetadata const& getMetadata() const {
        return m_metadata;
    }

private:

    WidgetMetadata m_metadata;
};

#endif