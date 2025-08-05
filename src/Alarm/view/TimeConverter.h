#ifndef TIME_CONVERTER_H
#define TIME_CONVERTER_H

#include <QDateTime>
#include <QObject>
#include <QString>

#include "AlarmPreferencesRepositoryIfc.h"

/**
 * Formats time and date for display in QML.
 * Provides conversion from timestamp to formatted strings in the user's preferred timezone.
 */
// TODO all system preferences should be moved to a common module (in Platform)
class TimeConverter : public QObject {
    Q_OBJECT

public:

    /**
     * Constructs a TimeConverter.
     * @param preferences Reference to the alarm preferences repository.
     */
    TimeConverter(AlarmPreferencesRepositoryIfc& preferences);

    /**
     * Formats the given timestamp as a time string (hh:mm).
     * @param utcTimestamp The time as a UNIX timestamp in UTC.
     * @return The formatted time string.
     */
    Q_INVOKABLE QString asTime(uint64_t const utcTimestamp);

    /**
     * Formats the given timestamp as a date string (e.g., "Saturday, 19. July 2025").
     * @param utcTimestamp The time as a UNIX timestamp in UTC.
     * @return The formatted date string
     */
    Q_INVOKABLE QString asDate(uint64_t const utcTimestamp);

    /**
     * Converts the given timestamp to a relative day time in the preferred timezone.
     * @param utcTimestamp The time as a UNIX timestamp in UTC.
     * @return The relative day time as a uint32_t in the preferred timezone.
     */
    Q_INVOKABLE uint32_t utcToRelativeTime(uint64_t const utcTimestamp);

    /**
     * Converts the given timestamp to a relative day time in the UTC timezone.
     * @param localTimestamp The time as a UNIX timestamp in the preferred timezone.
     * @return The relative day time as a uint32_t in UTC.
     */
    Q_INVOKABLE uint32_t relativeTimeToUtc(uint64_t const localTimestamp);

private:

    QDateTime toLocalDateTime(uint64_t const utcTimestamp);
    QDateTime fromLocalDateTime(uint64_t const localTimestamp);

    AlarmPreferencesRepositoryIfc& m_preferences;
};

#endif