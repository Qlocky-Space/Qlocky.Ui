#ifndef QLOCKY_MAIN_PAGE_VIEWMODEL_H
#define QLOCKY_MAIN_PAGE_VIEWMODEL_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "api/Mediator.h"
#include "Navigation/InteractiveNavigatorIfc.h"
#include "Widget.h"
#include "WidgetListModel.h"
#include "WidgetLoadedEvent.h"

/**
 * MainPageViewModel is responsible for managing the main page view model.
 * It handles the loading of widgets and updates the widget list view model.
 */
class MainPageViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(WidgetListModel const* widgets READ getWidgets CONSTANT)

public:

    explicit MainPageViewModel(Mediator& mediator);

    /**
     * Returns the widget list model.
     */
    WidgetListModel const* getWidgets() const {
        return &m_widgets;
    }

private:

    void onWidgetLoaded(WidgetLoadedEvent const& e);

    WidgetListModel m_widgets;
};

#endif