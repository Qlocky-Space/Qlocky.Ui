#ifndef TIME_FORMATTER_H
#define TIME_FORMATTER_H

#include <QDateTime>
#include <QObject>
#include <QString>

#include "internal/AlarmPreferencesRepositoryIfc.h"

class TimeFormatter : public QObject {
    Q_OBJECT

public:

    TimeFormatter(AlarmPreferencesRepositoryIfc& preferences);

    Q_INVOKABLE QString asTime(uint64_t const& date);
    Q_INVOKABLE QString asDate(uint64_t const& date);

private:

    QDateTime getLocalTime(uint64_t const timestamp);

    AlarmPreferencesRepositoryIfc& m_preferences;
};

#endif