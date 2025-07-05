#include "MainWindowViewModel.h"

#include "PageChangedEvent.h"

MainWindowViewModel::MainWindowViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_window {},
    m_pageUrl {DEFAULT_PAGE_URL} {
    mediator.subscribe<PageChangedEvent>([this](PageChangedEvent const& event) { onPageChanged(event.getPage()); });
}

void MainWindowViewModel::onPageChanged(Page const& page) {
    QString url {QString::fromStdString(std::string {page.url})};

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