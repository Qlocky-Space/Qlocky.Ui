#include "WidgetLoader.h"

#include <memory>

#include "Widget.h"
#include "WidgetLoadedEvent.h"

WidgetLoader::WidgetLoader(Mediator& mediator) :
    m_mediator(mediator) {
}

void WidgetLoader::loadWidget(WidgetMetadata const& metadata) {
    std::shared_ptr<Widget> widget = std::make_shared<Widget>(metadata);

    m_mediator.notify(WidgetLoadedEvent(widget));
}
