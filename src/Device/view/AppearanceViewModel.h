#ifndef APPEARANCE_VIEW_MODEL_H
#define APPEARANCE_VIEW_MODEL_H

#include <QObject>

#include "Mediator.h"
#include "SystemPreferencesRepositoryIfc.h"

class AppearanceViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool timeFormatBoolean READ getTimeFormatBoolean NOTIFY timeFormatChanged);

public:

    explicit AppearanceViewModel(Mediator& mediator, SystemPreferencesRepositoryIfc& repository);

    /**
     * Changes the TimeFormat
     * @param is24HourFormat True for 24H Format / False for 12H Format
     */
    Q_INVOKABLE void changeTimeFormat(bool is24HourFormat);

    bool getTimeFormatBoolean() const;

signals:
    void timeFormatChanged();

private:

    SystemPreferencesRepositoryIfc& m_repository;
};

#endif // APPEARANCE_VIEW_MODEL_H