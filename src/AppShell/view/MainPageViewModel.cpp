

#include "MainPageViewModel.h"

#include "WidgetLoadedEvent.h"

MainPageViewModel::MainPageViewModel(Mediator& mediator, WidgetListModel& widgetModel) :
    QObject {nullptr},
    m_widgets {widgetModel} {
    mediator.subscribe<WidgetLoadedEvent>([this](WidgetLoadedEvent const& event) { onWidgetLoaded(event.getWidget()); });
}

void MainPageViewModel::onWidgetLoaded(std::shared_ptr<Widget> widget) {
    m_widgets.addWidget(widget->getMetadata());
}
