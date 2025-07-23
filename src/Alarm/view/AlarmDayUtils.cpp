#include "AlarmDayUtils.h"

#include <QCoreApplication>

QString AlarmDayUtils::getDaysDisplay(DayOfWeekViewModel::Days const flags) {
    QStringList parts;

    constexpr DayOfWeekViewModel::Days Weekdays = DayOfWeekViewModel::Day::Monday | DayOfWeekViewModel::Day::Tuesday |
        DayOfWeekViewModel::Day::Wednesday | DayOfWeekViewModel::Day::Thursday |
        DayOfWeekViewModel::Day::Friday;
    constexpr DayOfWeekViewModel::Days Weekends = DayOfWeekViewModel::Day::Saturday | DayOfWeekViewModel::Day::Sunday;

    constexpr DayOfWeekViewModel::Days AllDays = Weekdays | Weekends;

    if (flags == AllDays) {
        return QCoreApplication::translate("AlarmDayUtils", "Every day");
    }
    if (flags == Weekends) {
        return QCoreApplication::translate("AlarmDayUtils", "Weekend");
    }
    if (flags == Weekdays) {
        return QCoreApplication::translate("AlarmDayUtils", "Weekday");
    }

    if (flags & DayOfWeekViewModel::Day::Monday) {
        parts << QCoreApplication::translate("AlarmDayUtils", "Mon");
    }
    if (flags & DayOfWeekViewModel::Day::Tuesday) {
        parts << QCoreApplication::translate("AlarmDayUtils", "Tue");
    }
    if (flags & DayOfWeekViewModel::Day::Wednesday) {
        parts << QCoreApplication::translate("AlarmDayUtils", "Wed");
    }
    if (flags & DayOfWeekViewModel::Day::Thursday) {
        parts << QCoreApplication::translate("AlarmDayUtils", "Thu");
    }
    if (flags & DayOfWeekViewModel::Day::Friday) {
        parts << QCoreApplication::translate("AlarmDayUtils", "Fri");
    }
    if (flags & DayOfWeekViewModel::Day::Saturday) {
        parts << QCoreApplication::translate("AlarmDayUtils", "Sat");
    }
    if (flags & DayOfWeekViewModel::Day::Sunday) {
        parts << QCoreApplication::translate("AlarmDayUtils", "Sun");
    }

    if (parts.isEmpty()) {
        return QCoreApplication::translate("AlarmDayUtils", "Only ring once");
    }

    return parts.join(", ");
}
