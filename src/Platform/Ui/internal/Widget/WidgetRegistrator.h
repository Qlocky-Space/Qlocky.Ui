#ifndef WIDGET_REGISTRATOR_H
#define WIDGET_REGISTRATOR_H

#include <map>
#include <string>

#include "Widget/WidgetMetadata.h"
#include "Widget/WidgetRegistratorIfc.h"
#include "WidgetLoader.h"

/**
 * @see WidgetRegistratorIfc
 */
class WidgetRegistrator : public WidgetRegistratorIfc {
public:

    /**
     * Constructor for the WidgetRegistrator class.
     */
    WidgetRegistrator(WidgetLoader& loader);

    /**
     * @see WidgetRegistratorIfc::registerWidget
     */
    void registerWidget(WidgetMetadata const& metadata) final;

private:

    WidgetLoader& m_loader;
    std::map<std::string, WidgetMetadata> m_widgets;
};

#endif