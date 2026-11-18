#ifndef APPEARANCE_VIEW_MODEL_H
#define APPEARANCE_VIEW_MODEL_H

#include <QObject>
#include <QString>
#include <QVariantList>

#include "Mediator.h"
#include "SystemPreferencesRepositoryIfc.h"
#include "TimeZoneProviderIfc.h"

class AppearanceViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool timeFormatBoolean READ getTimeFormatBoolean NOTIFY timeFormatChanged);
    Q_PROPERTY(QString timeZoneId READ getTimeZoneId NOTIFY timeZoneChanged);
    Q_PROPERTY(QString timeZoneLabel READ getTimeZoneLabel NOTIFY timeZoneChanged);
    Q_PROPERTY(QString selectedTimeZoneGroup READ getSelectedTimeZoneGroup WRITE setSelectedTimeZoneGroup NOTIFY selectedTimeZoneGroupChanged);
    Q_PROPERTY(QVariantList timeZoneGroups READ getTimeZoneGroups NOTIFY timeZoneGroupsChanged);

public:

    explicit AppearanceViewModel(Mediator& mediator, SystemPreferencesRepositoryIfc& repository, TimeZoneProviderIfc& timeZoneProvider);

    /**
     * Changes the TimeFormat
     * @param is24HourFormat True for 24H Format / False for 12H Format
     */
    Q_INVOKABLE void changeTimeFormat(bool is24HourFormat);

    /**
     * Reloads the time zone groups and preselects the group of the current time zone.
     * Should be called when the time zone selection dialog opens.
     */
    Q_INVOKABLE void resetTimeZoneSelection();

    /**
     * Persists the currently selected time zone group.
     * If the current time zone is already part of the selected group, nothing changes,
     * so that e.g. "Europe/Zurich" is not replaced by "Europe/Berlin".
     */
    Q_INVOKABLE void applySelectedTimeZone();

    bool getTimeFormatBoolean() const;

    QString getTimeZoneId() const;

    /**
     * @return Label of the current time zone, e.g. "UTC+01:00 Zurich".
     */
    QString getTimeZoneLabel() const;

    QString getSelectedTimeZoneGroup() const;
    void setSelectedTimeZoneGroup(QString const& groupId);

    /**
     * @return List of maps with keys: id, offset, cities, searchText, observesDst
     */
    QVariantList getTimeZoneGroups() const;

signals:
    void timeFormatChanged();
    void timeZoneChanged();
    void selectedTimeZoneGroupChanged();
    void timeZoneGroupsChanged();

private:

    SystemPreferencesRepositoryIfc& m_repository;
    TimeZoneProviderIfc& m_timeZoneProvider;

    QVariantList m_timeZoneGroups {};
    QString m_selectedTimeZoneGroup {};
};

#endif // APPEARANCE_VIEW_MODEL_H
