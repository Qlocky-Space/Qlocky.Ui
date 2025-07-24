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
    Q_PROPERTY(bool isAirplaneModeEnabled READ isAirplaneModeEnabled WRITE setAirplaneMode NOTIFY airplaneModeChanged)
    Q_PROPERTY(bool lightMode READ isLightModeEnabled WRITE setLightMode NOTIFY lightModeChanged)
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

    /**
     * Sets the network state.
     * @param enabled True to enable network, false to disable it.
     */
    Q_INVOKABLE void setNetworkState(bool enabled);

    /**
     * Checks if light mode is enabled.
     */
    bool isLightModeEnabled() const {
        return m_lightMode;
    }

    /**
     * Sets the airplane mode.
     * @param enabled True to enable airplane mode, false to disable it.
     */
    void setAirplaneMode(bool enabled);

    /**
     * Sets the light mode.
     * @param enabled True to enable light mode, false to disable it.
     */
    void setLightMode(bool enabled);

signals:
    void titleChanged();
    void networkStrengthChanged();
    void airplaneModeChanged();
    void lightModeChanged();

private:

    QString m_title;
    int32_t m_networkStrength; // -1 to 100, -1 means no network
    bool m_airplaneMode;
    bool m_lightMode;
};

#endif