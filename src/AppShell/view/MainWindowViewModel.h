#ifndef QLOCKY_MAIN_WINDOW_VIEW_H
#define QLOCKY_MAIN_WINDOW_VIEW_H

#include <QObject>
#include <QQmlEngine>
#include <QWindow>

class MainWindowViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QWindow* window READ getWindow WRITE setWindow)

public:

    explicit MainWindowViewModel(QObject* parent = nullptr);
    ~MainWindowViewModel();

    QWindow* getWindow() const {
        return m_window;
    }

private slots:
    void setWindow(QWindow* window);

private:

    QWindow* m_window;
};

#endif