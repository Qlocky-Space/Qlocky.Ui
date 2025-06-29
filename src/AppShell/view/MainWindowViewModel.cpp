

#include "MainWindowViewModel.h"

#include <iostream>

#include "WidgetLoadedEvent.h"

MainWindowViewModel::MainWindowViewModel(Mediator& mediator, WidgetListViewModel& widgetModel) :
    QObject {nullptr},
    m_window {},
    m_widgets {widgetModel} {
    // subscribe mediator callbacks
    mediator.subscribe<WidgetLoadedEvent>([this](WidgetLoadedEvent const& event) { onWidgetLoaded(event.getWidget()); });
}

void MainWindowViewModel::onWidgetLoaded(std::shared_ptr<Widget> widget) {
    m_widgets.addWidget(widget->getMetadata());
}

void MainWindowViewModel::setWindow(QWindow* window) {
    if (m_window != nullptr) {
        return;
    }

    m_window = window;

#ifndef OS_IS_LINUX
    window->showFullScreen();
#endif
}