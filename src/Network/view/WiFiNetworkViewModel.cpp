#include "WiFiNetworkViewModel.h"

WiFiNetworkViewModel::WiFiNetworkViewModel() :
    QObject(nullptr),
    m_signalStrength(0),
    m_connected(false) {
}

void WiFiNetworkViewModel::setSsid(QString const& ssid) {
    if (m_ssid != ssid) {
        m_ssid = ssid;
        emit ssidChanged();
    }
}

void WiFiNetworkViewModel::setConnected(bool connected) {
    if (m_connected != connected) {
        m_connected = connected;
        emit connectedChanged();
    }
}

void WiFiNetworkViewModel::setSignalStrength(int signalStrength) {
    if (m_signalStrength != signalStrength) {
        m_signalStrength = signalStrength;
        emit signalStrengthChanged();
    }
}
