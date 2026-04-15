#ifndef WIFI_PROFILE_DIALOG_VIEWMODEL_H
#define WIFI_PROFILE_DIALOG_VIEWMODEL_H

#include <QObject>
#include <QString>

#include "NetworkServiceIfc.h"

/**
 * ViewModel for the WiFi profile dialog.
 *
 * Provides properties and logic for editing or displaying a WiFi profile.
 */
class WiFiProfileDialogViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString securityType READ securityType WRITE setSecurityType NOTIFY securityTypeChanged)

public:

    explicit WiFiProfileDialogViewModel(NetworkServiceIfc& networkService);

    /**
     * @return The SSID of the WiFi network.
     */
    QString ssid() const {
        return m_ssid;
    }

    /**
     * @param ssid The SSID to set.
     */
    void setSsid(QString const& ssid);

    /**
     * @return The password for the WiFi network.
     */
    QString password() const {
        return m_password;
    }

    /**
     * @param password The password to set.
     */
    void setPassword(QString const& password);

    /**
     * @return The security type of the WiFi network.
     */
    QString securityType() const {
        return m_securityType;
    }

    /**
     * @param securityType The security type to set.
     */
    void setSecurityType(QString const& securityType);

    /**
     * Connects to the WiFi network with the current properties.
     */
    Q_INVOKABLE void connectTo();

signals:
    void ssidChanged();
    void passwordChanged();
    void securityTypeChanged();

private:

    NetworkServiceIfc& m_networkService;

    QString m_ssid;
    QString m_password;
    QString m_securityType;
};

#endif