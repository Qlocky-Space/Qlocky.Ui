#ifndef QLOCKY_MAIN_WINDOW_VIEW_H
#define QLOCKY_MAIN_WINDOW_VIEW_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QWindow>

class MainWindowViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ getWindow WRITE setWindow)
    QML_ELEMENT

public:

    explicit MainWindowViewModel(QObject* parent = nullptr);

    QWindow* getWindow() const {
        return m_window;
    }

private slots:
    void setWindow(QWindow* window);

private:

    QWindow* m_window;
};

#endif