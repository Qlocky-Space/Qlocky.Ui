
#include "WidgetRegistrator.h"

WidgetRegistrator::WidgetRegistrator(WidgetLoader& loader) :
    m_loader(loader),
    m_widgets() {
}

void WidgetRegistrator::registerWidget(WidgetMetadata const& metadata) {
    if (m_widgets.find(metadata.getName()) != m_widgets.end()) {
        // Widget already registered, handle accordingly (e.g., log a warning or throw an exception)
        return;
    }

    m_widgets[metadata.getName()] = metadata;

    m_loader.loadWidget(metadata);
}
