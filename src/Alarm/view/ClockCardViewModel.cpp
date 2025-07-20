#include "ClockCardViewModel.h"

#include <iostream>
#include <QTimeZone>

#include "events/AlarmActivatedEvent.h"

ClockCardViewModel::ClockCardViewModel(Mediator& mediator) :
    QObject {nullptr},
    m_timestamp {} {
    mediator.subscribe<TimeChangedEvent>(this, &ClockCardViewModel::onTimeChanged);

    // TODO remove demo code
    mediator.subscribe<AlarmActivatedEvent>([](AlarmActivatedEvent const& event) {
        std::cout << "Alarm activated: " << event.alarm.name << std::endl;
    });
}

void ClockCardViewModel::onTimeChanged(TimeChangedEvent const& event) {
    m_timestamp = event.getValue();

    emit timestampChanged();
}
