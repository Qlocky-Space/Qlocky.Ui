#ifndef QLOCKY_MAIN_PAGE_VIEWMODEL_H
#define QLOCKY_MAIN_PAGE_VIEWMODEL_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "api/Mediator.h"
#include "Navigation/NavigatorIfc.h"
#include "Widget.h"
#include "WidgetListModel.h"

/**
 * MainPageViewModel is responsible for managing the main page view model.
 * It handles the loading of widgets and updates the widget list view model.
 */
class MainPageViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(WidgetListModel* widgets READ getWidgets CONSTANT)

public:

    explicit MainPageViewModel(Mediator& mediator, WidgetListModel& widgetModel);

    /**
     * Returns the widget list model.
     */
    WidgetListModel* getWidgets() const {
        return &m_widgets;
    }

private:

    void onWidgetLoaded(std::shared_ptr<Widget> widget);

    WidgetListModel& m_widgets;
};

#endif