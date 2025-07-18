#include "ClockCardViewModel.h"

#include <iostream>
#include <QTimeZone>

#include "internal/AlarmPreferencesDefault.h"

ClockCardViewModel::ClockCardViewModel(Mediator& mediator, PersistenceServiceIfc& preferences) :
    QObject {nullptr},
    m_date {},
    m_time {},
    m_preferences {preferences} {
    mediator.subscribe<TimeChangedEvent>(this, &ClockCardViewModel::onTimeChanged);
}

void ClockCardViewModel::onTimeChanged(TimeChangedEvent const& event) {
    QDateTime const dt {getLocalTime(event.getValue())};

    m_date = formatDate(dt);
    m_time = formatTime(dt);

    emit timeChanged();
    emit dateChanged();
}

QDateTime ClockCardViewModel::getLocalTime(DateTime const timestamp) {
    auto& ctx = m_preferences.getContext(AlarmPreferencesDefault::ALARM_PREFERENCES_NAMESPACE);
    std::string const prefTimeZone {ctx.getString(AlarmPreferencesDefault::PROP_TIMEZONE)};

    QTimeZone const timeZone {prefTimeZone.c_str()};
    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(timestamp, QTimeZone::utc())};

    return unixTimestamp.toTimeZone(timeZone);
}

QString ClockCardViewModel::formatTime(QDateTime const& time) {
    auto& ctx {m_preferences.getContext(AlarmPreferencesDefault::ALARM_PREFERENCES_NAMESPACE)};
    std::string const hFormat {ctx.getString(AlarmPreferencesDefault::PROP_24H_FORMAT)};

    bool const showSeparator {(time.toSecsSinceEpoch() % 2U) == 0U};
    QString format {QString::fromStdString(hFormat)};
    format.append(showSeparator ? ":" : " ");
    format.append("mm");

    return time.toString(format);
}

QString ClockCardViewModel::formatDate(QDateTime const& time) {
    return time.toString("dddd, d. MMMM yyyy");
}
