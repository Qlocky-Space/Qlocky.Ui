#ifndef WIDGET_LOADER_H
#define WIDGET_LOADER_H

#include "api/Mediator.h"
#include "Widget/WidgetLoaderIfc.h"
#include "Widget/WidgetMetadata.h"

/**
 * @see WidgetLoaderIfc
 */
class WidgetLoader : public WidgetLoaderIfc {
public:

    /**
     * Constructor for the WidgetLoader class.
     *
     * @param mediator The mediator instance used for communication between components.
     */
    WidgetLoader(Mediator& mediator);

    /**
     * @see WidgetLoaderIfc::loadWidget
     */
    void loadWidget(WidgetMetadata const& metadata) final;

private:

    Mediator& m_mediator;
};

#endif