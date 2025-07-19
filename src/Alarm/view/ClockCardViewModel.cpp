#include "ClockCardViewModel.h"

#include <iostream>
#include <QTimeZone>

ClockCardViewModel::ClockCardViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_timestamp {} {
    mediator.subscribe<TimeChangedEvent>(this, &ClockCardViewModel::onTimeChanged);
}

void ClockCardViewModel::onTimeChanged(TimeChangedEvent const& event) {
    m_timestamp = event.getValue();

    emit timestampChanged();
}
