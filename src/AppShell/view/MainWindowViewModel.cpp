#include "MainWindowViewModel.h"

MainWindowViewModel::MainWindowViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_window {},
    m_pageUrl {} {
    mediator.subscribe<NavigateToEvent>(this, &MainWindowViewModel::onPageChanged);
}

void MainWindowViewModel::onPageChanged(NavigateToEvent const& event) {
    if (event.getMeta().type != InteractiveMeta::Type::Page) {
        return;
    }

    QString url {QString::fromStdString(std::string {event.getMeta().qmlPath})};

    if (m_pageUrl != url) {
        m_pageUrl = url;
        emit pageUrlChanged();
    }
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