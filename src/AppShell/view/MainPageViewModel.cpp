

#include "MainPageViewModel.h"

MainPageViewModel::MainPageViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_widgets {} {
    mediator.subscribe<WidgetLoadedEvent>(this, &MainPageViewModel::onWidgetLoaded);
}

void MainPageViewModel::onWidgetLoaded(WidgetLoadedEvent const& e) {
    m_widgets.addWidget(e.getWidget()->getMetadata());
}
