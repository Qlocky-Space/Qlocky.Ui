#include "MainWindowViewModel.h"

MainWindowViewModel::MainWindowViewModel(Mediator& mediator) :
    QObject {nullptr},
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