

#include "MainWindowViewModel.h"

MainWindowViewModel::MainWindowViewModel(QObject* parent) :
    QObject {parent},
    m_window {} {
}

void MainWindowViewModel::setWindow(QWindow* window) {
    if (m_window != nullptr) {
        return;
    }

    m_window = window;

#ifndef OS_IS_LINUX
    window->showFullScreen();
#endif
}