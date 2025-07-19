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
class TimeFormatter : public QObject {
    Q_OBJECT

public:

    /**
     * Constructs a TimeFormatter.
     * @param preferences Reference to the alarm preferences repository.
     */
    TimeFormatter(AlarmPreferencesRepositoryIfc& preferences);

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
    QDateTime toLocalDateTime(uint64_t const timestamp);

private:

    AlarmPreferencesRepositoryIfc& m_preferences;
};

#endif // SRC_ALARM_VIEW_TIMEFORMATTER_H