

#include "MainWindowViewModel.h"

#include "WidgetLoadedEvent.h"

MainWindowViewModel::MainWindowViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_window {} {

    mediator.subscribe<WidgetLoadedEvent>([this](WidgetLoadedEvent const& event) { onWidgetLoaded(event.getWidget()); });
}

void MainWindowViewModel::onWidgetLoaded(WidgetIfc& widget) {
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