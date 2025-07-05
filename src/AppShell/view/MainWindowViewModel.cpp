#include "MainWindowViewModel.h"

#include "Navigation/PageChangedEvent.h"

MainWindowViewModel::MainWindowViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_window {},
    m_pageUrl {} {
    mediator.subscribe<PageChangedEvent>(this, &MainWindowViewModel::onPageChanged);
}

void MainWindowViewModel::onPageChanged(PageChangedEvent const& event) {
    QString url {QString::fromStdString(std::string {event.getPage().url})};

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