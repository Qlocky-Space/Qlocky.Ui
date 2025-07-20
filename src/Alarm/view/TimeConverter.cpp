#include "TimeConverter.h"

#include <iostream>
#include <QTimeZone>

TimeConverter::TimeConverter(AlarmPreferencesRepositoryIfc& preferences) :
    m_preferences {preferences} {
}

QString TimeConverter::asTime(uint64_t const utcTimestamp) {
    QDateTime localTime = toLocalDateTime(utcTimestamp);

    bool const showSeparator {(localTime.toSecsSinceEpoch() % 2U) == 0U};
    std::string format {m_preferences.getTimeFormat()};

    size_t const separatorPos = format.find(":");
    if (separatorPos != std::string::npos) {
        format = format.replace(separatorPos, 1, showSeparator ? ":" : " ");
    }
    else {
        // If no separator is found, default to "HH:mm"
        format = "HH:mm";
    }

    return localTime.toString(QString::fromStdString(format));
}

QString TimeConverter::asDate(uint64_t const utcTimestamp) {
    QDateTime localTime = toLocalDateTime(utcTimestamp);
    return localTime.toLocalTime().toString("dddd, d. MMMM yyyy");
}

QDateTime TimeConverter::toLocalDateTime(uint64_t const utcTimestamp) {
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime unixTimestamp {QDateTime::fromSecsSinceEpoch(static_cast<qint64>(utcTimestamp), QTimeZone::utc())};
    return unixTimestamp.toTimeZone(timeZone);
}

QDateTime TimeConverter::fromLocalDateTime(uint64_t const localTimestamp) {
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime unixTimestamp {QDateTime::fromSecsSinceEpoch(static_cast<qint64>(localTimestamp), timeZone)};
    return unixTimestamp.toTimeZone(timeZone);
}

uint32_t TimeConverter::utcToRelativeTime(uint64_t const utcTimestamp) {
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime dateTime {QDateTime::fromSecsSinceEpoch(static_cast<qint64>(utcTimestamp), QTimeZone::utc())};
    dateTime.setTimeZone(timeZone);

    auto localTime = dateTime.time().addSecs(dateTime.offsetFromUtc());

    return localTime.msecsSinceStartOfDay() / 1000U;
}

uint32_t TimeConverter::relativeTimeToUtc(uint64_t const localTimestamp) {
    QTimeZone const timeZone {m_preferences.getTimeZone().c_str()};
    QDateTime dateTime {QDateTime::fromSecsSinceEpoch(static_cast<qint64>(localTimestamp), timeZone)};

    auto utcTime = dateTime.toUTC().time().addSecs(-dateTime.offsetFromUtc());

    return utcTime.msecsSinceStartOfDay() / 1000U;
}
