#ifndef QLOCKY_MAIN_WINDOW_H
#define QLOCKY_MAIN_WINDOW_H

#include <QQmlApplicationEngine>

#include "api/MainWindowIfc.h"

class MainWindow final : public MainWindowIfc {
public:

    MainWindow() = default;
    ~MainWindow() final = default;

private:
};

#endif