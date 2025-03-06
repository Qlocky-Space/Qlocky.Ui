

#include "MainWindowViewModel.h"

MainWindowViewModel::MainWindowViewModel(QObject* parent) :
    QObject {parent},
    m_window {} {
}

MainWindowViewModel::~MainWindowViewModel() {
}

void MainWindowViewModel::setWindow(QWindow* window) {
    if (m_window != nullptr) {
        return;
    }

    m_window = window;
    window->showFullScreen();
}