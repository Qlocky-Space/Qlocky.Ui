#ifndef QLOCKY_MAIN_WINDOW_VIEW_H
#define QLOCKY_MAIN_WINDOW_VIEW_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "api/Mediator.h"
#include "WidgetIfc.h"

class MainWindowViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ getWindow WRITE setWindow)

public:

    explicit MainWindowViewModel(Mediator& mediator);

    QWindow* getWindow() const {
        return m_window;
    }

private slots:
    void setWindow(QWindow* window);

private:

    void onWidgetLoaded(WidgetIfc& widget);

    QWindow* m_window;
};

#endif