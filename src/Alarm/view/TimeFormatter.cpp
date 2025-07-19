#include "TimeFormatter.h"

#include <iostream>
#include <QTimeZone>

TimeFormatter::TimeFormatter(AlarmPreferencesRepositoryIfc& preferences) :
    m_preferences {preferences} {
}

QString TimeFormatter::asTime(uint64_t const date) {
    QDateTime localTime = toLocalDateTime(date);

    bool const showSeparator {(localTime.toSecsSinceEpoch() % 2U) == 0U};
    std::string format {m_preferences.getTimeFormat()};
    format = format.replace(format.find(":"), 1, showSeparator ? ":" : " ");
    QString const qFormat {QString::fromStdString(format)};

    return localTime.toString(qFormat);
}

QString TimeFormatter::asDate(uint64_t const date) {
    QDateTime localTime = toLocalDateTime(date);
    QString t = localTime.toString("dddd, d. MMMM yyyy");
    return t;
}

QDateTime TimeFormatter::toLocalDateTime(uint64_t const timestamp) {
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(static_cast<qint64>(timestamp), QTimeZone::utc())};
    return unixTimestamp.toTimeZone(timeZone);
}
