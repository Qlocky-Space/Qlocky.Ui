#ifndef WIDGET_LOADED_EVENT_H
#define WIDGET_LOADED_EVENT_H

#include <memory>

#include "api/EventIfc.h"
#include "Widget.h"

class WidgetLoadedEvent : public EventIfc {
public:

    /**
     * Constructs a WidgetLoadedEvent with the given widget.
     *
     * @param widget The widget that has been loaded.
     */
    explicit WidgetLoadedEvent(std::shared_ptr<Widget> widget) :
        m_widget {widget} {
    }

    /**
     * Returns the widget associated with this event.
     *
     * @return The loaded widget.
     */
    std::shared_ptr<Widget> getWidget() const {
        return m_widget;
    }

private:

    std::shared_ptr<Widget> m_widget;
};

#endif