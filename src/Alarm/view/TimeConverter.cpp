#include <iostream>
#include <QTimeZone>

#include "TimeConverter.h"

TimeConverter::TimeConverter(AlarmPreferencesRepositoryIfc& preferences) :
    m_preferences {preferences} {
}

QString TimeConverter::asTime(uint64_t const date) {
    QDateTime localTime = toLocalDateTime(date);

    bool const showSeparator {(localTime.toSecsSinceEpoch() % 2U) == 0U};
    std::string format {m_preferences.getTimeFormat()};
    format = format.replace(format.find(":"), 1, showSeparator ? ":" : " ");
    QString const qFormat {QString::fromStdString(format)};

    return localTime.toString(qFormat);
}

QString TimeConverter::asDate(uint64_t const date) {
    QDateTime localTime = toLocalDateTime(date);
    QString t = localTime.toString("dddd, d. MMMM yyyy");
    return t;
}

QDateTime TimeConverter::toLocalDateTime(uint64_t const timestamp) {
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(static_cast<qint64>(timestamp), QTimeZone::utc())};
    return unixTimestamp.toTimeZone(timeZone);
}

QDateTime TimeConverter::fromLocalDateTime(uint64_t const timestamp) {
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime const unixTimestamp {QDateTime::fromSecsSinceEpoch(static_cast<qint64>(timestamp), timeZone)};
    return unixTimestamp.toTimeZone(QTimeZone::utc());
}

uint32_t TimeConverter::toLocalRelativeTime(uint64_t const timestamp) {
    return toLocalDateTime(timestamp).time().msecsSinceStartOfDay() / 1000U;
}

uint32_t TimeConverter::toUtcRelativeTime(uint64_t const timestamp) {
    return fromLocalDateTime(timestamp).time().msecsSinceStartOfDay() / 1000U;
}
