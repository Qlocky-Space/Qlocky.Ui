#include "WiFiProfileDialogViewModel.h"

#include "NetworkProfileNew.h"

WiFiProfileDialogViewModel::WiFiProfileDialogViewModel(NetworkServiceIfc& networkService) :
    QObject(nullptr),
    m_networkService(networkService),
    m_ssid(""),
    m_password(""),
    m_securityType("WPA-PSK") {
}

void WiFiProfileDialogViewModel::setSsid(QString const& ssid) {
    if (m_ssid != ssid) {
        m_ssid = ssid;
        emit ssidChanged();
    }
}

void WiFiProfileDialogViewModel::setPassword(QString const& password) {
    if (m_password != password) {
        m_password = password;
        emit passwordChanged();
    }
}

void WiFiProfileDialogViewModel::setSecurityType(QString const& securityType) {
    if (m_securityType != securityType) {
        m_securityType = securityType;
        emit securityTypeChanged();
    }
}

void WiFiProfileDialogViewModel::connectTo() {
    if (m_ssid.isEmpty()) {
        qWarning("SSID is required to create a WiFi profile.");
        return;
    }

    NetworkProfileNew profile;
    profile.Ssid = m_ssid.toStdString();
    profile.Psk = m_password.toStdString();
    profile.SecurityType = m_securityType.toStdString();
    profile.AutoConnect = true;

    m_networkService.connectTo(profile);
}