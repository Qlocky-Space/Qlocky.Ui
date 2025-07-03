#include "ClockCardViewModel.h"

#include <iostream>
#include <QDateTime>
#include <QTimeZone>

ClockCardViewModel::ClockCardViewModel(Mediator& mediator, PingCommand& pingCommand, PreferencesServiceIfc& preferences) :
    QObject {nullptr},
    m_pingCommand {pingCommand},
    m_date {},
    m_time {},
    m_preferences {preferences} {
    mediator.subscribe<TimeChangedEvent>([this](auto e) { onTimeChanged(e); });
}

void ClockCardViewModel::onTimeChanged(TimeChangedEvent const& event) {
    static std::string const defaultTimeZone {"Europe/Zurich"};

    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(event.getValue(), QTimeZone::utc())};

    auto& ctx = m_preferences.getContext("Alarm");
    std::string const prefTimeZone {ctx.getString("TimeZone", defaultTimeZone)};
    QTimeZone timeZone {prefTimeZone.c_str()};
    QDateTime const dt {unixTimestamp.toTimeZone(timeZone)};

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
