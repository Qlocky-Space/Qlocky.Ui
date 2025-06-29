#ifndef QLOCKY_MAIN_WINDOW_VIEW_H
#define QLOCKY_MAIN_WINDOW_VIEW_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "api/Mediator.h"
#include "Widget.h"
#include "WidgetListViewModel.h"

class MainWindowViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ getWindow WRITE setWindow)

public:

    explicit MainWindowViewModel(Mediator& mediator, WidgetListViewModel& widgetModel);

    QWindow* getWindow() const {
        return m_window;
    }

private slots:
    void setWindow(QWindow* window);

private:

    void onWidgetLoaded(std::shared_ptr<Widget> widget);

    QWindow* m_window;
    WidgetListViewModel& m_widgets;
};

#endif