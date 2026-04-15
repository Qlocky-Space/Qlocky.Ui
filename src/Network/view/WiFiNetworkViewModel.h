#ifndef WIFI_NETWORK_VIEW_MODEL_H
#define WIFI_NETWORK_VIEW_MODEL_H

#include <QObject>
#include <QString>

/**
 * WiFiNetworkViewModel represents a Wi-Fi network with properties such as SSID, signal strength, and connection status.
 */
class WiFiNetworkViewModel final : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString ssid READ ssid WRITE setSsid NOTIFY ssidChanged)
    Q_PROPERTY(int signalStrength READ signalStrength WRITE setSignalStrength NOTIFY signalStrengthChanged)
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)

public:

    explicit WiFiNetworkViewModel();
    ~WiFiNetworkViewModel() final = default;

    /**
     * Gets the SSID of the Wi-Fi network.
     * @return The SSID of the network.
     */
    QString ssid() const {
        return m_ssid;
    }

    /**
     * Sets the SSID of the Wi-Fi network.
     * @param ssid The SSID to set.
     */
    void setSsid(QString const& ssid);

    /**
     * Gets the connection status of the Wi-Fi network.
     * @return True if connected, false otherwise.
     */
    bool connected() const {
        return m_connected;
    }

    /**
     * Sets the connection status of the Wi-Fi network.
     * @param connected True to set as connected, false to set as disconnected.
     */
    void setConnected(bool connected);

    /**
     * Gets the signal strength of the Wi-Fi network.
     * @return The signal strength as an integer.
     */
    int signalStrength() const {
        return m_signalStrength;
    }

    /**
     * Sets the signal strength of the Wi-Fi network.
     * @param signalStrength The signal strength to set.
     */
    void setSignalStrength(int signalStrength);

signals:
    void ssidChanged();
    void connectedChanged();
    void signalStrengthChanged();

private:

    QString m_ssid;
    int m_signalStrength;
    bool m_connected;
};

#endif