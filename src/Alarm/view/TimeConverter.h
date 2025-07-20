#ifndef SRC_ALARM_VIEW_TIMEFORMATTER_H
#define SRC_ALARM_VIEW_TIMEFORMATTER_H

#include <QDateTime>
#include <QObject>
#include <QString>

#include "internal/AlarmPreferencesRepositoryIfc.h"

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
     * @param date The time as a UNIX timestamp.
     * @return The formatted time string.
     */
    Q_INVOKABLE QString asTime(uint64_t const date);

    /**
     * Formats the given timestamp as a date string (e.g., "Saturday, 19. July 2025").
     * @param date The time as a UNIX timestamp.
     * @return The formatted date string.
     */
    Q_INVOKABLE QString asDate(uint64_t const date);

    /**
     * Converts the given timestamp to a QDateTime in the preferred timezone.
     * @param timestamp The time as a UNIX timestamp.
     * @return The QDateTime in the preferred timezone.
     */
    Q_INVOKABLE QDateTime toLocalDateTime(uint64_t const timestamp);

    /**
     * Converts the given timestamp to a QDateTime in the UTC timezone.
     * @param timestamp The time as a UNIX timestamp.
     * @return The QDateTime in the preferred timezone.
     */
    Q_INVOKABLE QDateTime fromLocalDateTime(uint64_t const timestamp);

    /**
     * Converts the given timestamp to a relative day time in the preferred timezone.
     * @param timestamp The time as a UNIX timestamp.
     * @return The relative day time as a uint32_t.
     */
    Q_INVOKABLE uint32_t toLocalRelativeTime(uint64_t const timestamp);

    /**
     * Converts the given timestamp to a relative day time in the UTC timezone.
     * @param timestamp The time as a UNIX timestamp.
     * @return The relative day time as a uint32_t.
     */
    Q_INVOKABLE uint32_t toUtcRelativeTime(uint64_t const timestamp);

private:

    AlarmPreferencesRepositoryIfc& m_preferences;
};

#endif // SRC_ALARM_VIEW_TIMEFORMATTER_H