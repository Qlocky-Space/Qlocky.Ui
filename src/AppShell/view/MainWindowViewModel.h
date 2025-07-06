#ifndef QLOCKY_MAIN_WINDOW_VIEW_H
#define QLOCKY_MAIN_WINDOW_VIEW_H

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

#include "api/Mediator.h"

/**
 * MainWindowViewModel is responsible for managing the main window view model.
 * It handles the window itself and navigation between pages
 */
class MainWindowViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ getWindow WRITE setWindow)

public:

    explicit MainWindowViewModel(Mediator& mediator);

    QWindow* getWindow() const {
        return m_window;
    }

signals:
    void pageUrlChanged();

private slots:
    void setWindow(QWindow* window);

private:

    QWindow* m_window;
};

#endif