#include "ClockCardViewModel.h"

#include <iostream>
#include <QTimeZone>

#include "internal/AlarmPreferencesDefault.h"

ClockCardViewModel::ClockCardViewModel(Mediator& mediator, PingCommand& pingCommand, PreferencesServiceIfc& preferences) :
    QObject {nullptr},
    m_pingCommand {pingCommand},
    m_date {},
    m_time {},
    m_preferences {preferences} {
    mediator.subscribe<TimeChangedEvent>([this](auto e) { onTimeChanged(e); });
}

void ClockCardViewModel::onTimeChanged(TimeChangedEvent const& event) {
    QDateTime const dt {getLocalTime(event.getValue())};

    m_date = formatDate(dt);
    m_time = formatTime(dt);

    emit timeChanged();
    emit dateChanged();
}

QDateTime ClockCardViewModel::getLocalTime(DateTime const timestamp) {
    auto& ctx = m_preferences.getContext("Alarm");
    std::string const prefTimeZone {ctx.getString("TimeZone", AlarmPreferencesDefault::DEFAULT_TIMEZONE)};

    QTimeZone const timeZone {prefTimeZone.c_str()};
    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(timestamp, QTimeZone::utc())};

    return unixTimestamp.toTimeZone(timeZone);
}

QString ClockCardViewModel::formatTime(QDateTime const& time) {
    auto& ctx = m_preferences.getContext("Alarm");
    std::string const hFormat {ctx.getString("24HFormat", AlarmPreferencesDefault::DEFAULT_24H_FORMAT)};

    bool const showSeperator {(time.toSecsSinceEpoch() % 2U) == 0U};
    std::string format {};
    format.append(hFormat);
    format.append(showSeperator ? ':' : ' ');
    format.append("mm");

    return time.toString(format);
}

QString ClockCardViewModel::formatDate(QDateTime const& time) {
    return time.toString("dddd, d. MMMM yyyy");
}
