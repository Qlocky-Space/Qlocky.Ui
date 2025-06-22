#ifndef WIDGET_LOADED_EVENT_H
#define WIDGET_LOADED_EVENT_H

#include "api/EventIfc.h"

class WidgetLoadedEvent : public EventIfc {
public:

    /**
     * Constructs a WidgetLoadedEvent with the given widget.
     *
     * @param widget The widget that has been loaded.
     */
    explicit WidgetLoadedEvent(WidgetIfc& widget) :
        m_widget {widget} {
    }

    /**
     * Returns the widget associated with this event.
     *
     * @return The loaded widget.
     */
    WidgetIfc& getWidget() const {
        return m_widget;
    }

private:

    WidgetIfc& m_widget;
};

#endif