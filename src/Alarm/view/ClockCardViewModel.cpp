#include "ClockCardViewModel.h"

#include <QDateTime>
#include <QTimeZone>

ClockCardViewModel::ClockCardViewModel(Mediator& mediator, PingCommand& pingCommand) :
    QObject {nullptr},
    m_pingCommand {pingCommand},
    m_date {},
    m_time {} {
    mediator.subscribe<TimeChangedEvent>([this](auto e) { onTimeChanged(e); });
}

void ClockCardViewModel::onTimeChanged(TimeChangedEvent const& event) {
    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(event.getValue(), QTimeZone::utc())};

    // TODO [https://github.com/Qlocky-Space/Qlocky.Ui/issues/13] this is a temporary solution, time zone should be configurable
    QTimeZone swissTz("Europe/Zurich");
    QDateTime const dt {unixTimestamp.toTimeZone(swissTz)};

    m_date = dt.toString("dddd, d. MMMM yyyy");

    bool const showSeperator {(event.getValue() % 2U) == 0U};
    if (showSeperator) {
        m_time = dt.toString("HH:mm");
    }
    else {
        m_time = dt.toString("HH mm");
    }

    emit timeChanged();
    emit dateChanged();
}
