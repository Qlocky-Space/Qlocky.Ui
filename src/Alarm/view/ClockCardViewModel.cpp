#include "ClockCardViewModel.h"

#include <iostream>
#include <QTimeZone>

ClockCardViewModel::ClockCardViewModel(Mediator& mediator, AlarmPreferencesRepositoryIfc& preferences) :
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
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(timestamp, QTimeZone::utc())};

    return unixTimestamp.toTimeZone(timeZone);
}

QString ClockCardViewModel::formatTime(QDateTime const& time) {
    bool const showSeparator {(time.toSecsSinceEpoch() % 2U) == 0U};
    std::string format {m_preferences.getTimeFormat()};
    format = format.replace(format.find(":"), 1, showSeparator ? ":" : "");
    QString qFormat {QString::fromStdString(format)};

    return time.toString(qFormat);
}

QString ClockCardViewModel::formatDate(QDateTime const& time) {
    return time.toString("dddd, d. MMMM yyyy");
}
