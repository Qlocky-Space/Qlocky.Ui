#ifndef DAY_OF_WEEK_VIEW_MODEL_H
#define DAY_OF_WEEK_VIEW_MODEL_H

#include <QFlags>
#include <QObject>

/**
 * Represents the days of the week for alarm scheduling.
 * This class provides an enumeration for each day and a flags type for combinations.
 */
class DayOfWeekViewModel : public QObject {
    Q_OBJECT

public:

    enum class Day {
        None = 0,
        Monday = 1 << 0,
        Tuesday = 1 << 1,
        Wednesday = 1 << 2,
        Thursday = 1 << 3,
        Friday = 1 << 4,
        Saturday = 1 << 5,
        Sunday = 1 << 6,
    };

    Q_DECLARE_FLAGS(Days, Day)
    Q_FLAG(Days)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(DayOfWeekViewModel::Days)

#endif