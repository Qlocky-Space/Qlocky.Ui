#ifndef ALARM_ALARM_DAY_UTILS_H
#define ALARM_ALARM_DAY_UTILS_H

#include <QObject>
#include <QString>
#include <vector>

#include "AlarmEntity.h"
#include "DayOfWeekViewModel.h"

/**
 * Utility class for handling day-related operations for alarms.
 */
class AlarmDayUtils : public QObject {
    Q_OBJECT

public:

    /**
     * Gets a human-readable representation of the enabled days
     *
     * @param alarm The alarm to get days for
     * @return String representation (e.g., "Mon, Wed, Fri")
     */
    Q_INVOKABLE static QString getDaysDisplay(DayOfWeekViewModel::Days const flags);
};

#endif