

#include "MainPageViewModel.h"

MainPageViewModel::MainPageViewModel(Mediator& mediator, WidgetListModel& widgetModel) :
    QObject {nullptr},
    m_widgets {widgetModel} {
    mediator.subscribe<WidgetLoadedEvent>(this, &MainPageViewModel::onWidgetLoaded);
}

void MainPageViewModel::onWidgetLoaded(WidgetLoadedEvent const& e) {
    m_widgets.addWidget(e.getWidget()->getMetadata());
}
