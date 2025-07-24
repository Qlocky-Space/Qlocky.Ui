#ifndef QLOCKY_STATUS_BAR_VIEWMODEL_H
#define QLOCKY_STATUS_BAR_VIEWMODEL_H

#include <QObject>
#include <QString>

#include "api/Mediator.h"

/**
 * StatusBarViewModel is responsible for managing the status bar view model.
 */
class StatusBarViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int32_t networkStrength READ getNetworkStrength NOTIFY networkStrengthChanged)
    Q_PROPERTY(bool isAirplaneModeEnabled READ isAirplaneModeEnabled NOTIFY airplaneModeChanged)
    Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged)

public:

    explicit StatusBarViewModel(Mediator& mediator);

    /**
     * Returns the current network strength.
     */
    int32_t getNetworkStrength() const {
        return m_networkStrength;
    }

    /**
     * Returns the current title.
     */
    QString getTitle() const {
        return m_title;
    }

    /**
     * Checks if airplane mode is enabled.
     */
    bool isAirplaneModeEnabled() const {
        return m_airplaneMode;
    }

signals:
    void titleChanged();
    void networkStrengthChanged();
    void airplaneModeChanged();

private:

    QString m_title;
    int32_t m_networkStrength; // -1 to 100, -1 means no network
    bool m_airplaneMode;
};

#endif