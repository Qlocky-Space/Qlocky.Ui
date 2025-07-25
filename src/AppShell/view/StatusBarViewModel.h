#ifndef QLOCKY_STATUS_BAR_VIEWMODEL_H
#define QLOCKY_STATUS_BAR_VIEWMODEL_H

#include <QFloat16>
#include <QObject>
#include <QString>

#include "api/Mediator.h"
#include "events/NetworkStatusEvent.h"
#include "NetworkServiceIfc.h"

/**
 * VolumeType is an enumeration representing the different types of volume settings.
 */
class VolumeType : public QObject {
    Q_OBJECT

public:

    enum class Level {
        Mute,
        Vibration,
        Acoustic
    };
    Q_ENUM(Level)
};

/**
 * StatusBarViewModel is responsible for managing the status bar view model.
 */
class StatusBarViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(int32_t networkStrength READ getNetworkStrength NOTIFY networkStrengthChanged)
    Q_PROPERTY(QString ssid READ ssid NOTIFY ssidChanged)
    Q_PROPERTY(bool isAirplaneModeEnabled READ isAirplaneModeEnabled WRITE setAirplaneMode NOTIFY airplaneModeChanged)
    Q_PROPERTY(bool lightMode READ isLightModeEnabled WRITE setLightMode NOTIFY lightModeChanged)
    Q_PROPERTY(QString title READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(float brightness READ getBrightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(float volume READ getVolume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(VolumeType::Level volumeType READ getVolumeType WRITE setVolumeType NOTIFY volumeTypeChanged)

public:

    explicit StatusBarViewModel(Mediator& mediator, NetworkServiceIfc& networkService);

    /**
     * Returns the current network strength.
     */
    int32_t getNetworkStrength() const {
        return m_networkStrength;
    }

    /**
     * Returns the current SSID of the connected network.
     * @return The SSID as a QString.
     */
    QString ssid() const {
        return m_ssid;
    }

    /**
     * Sets the SSID of the connected network.
     * @param ssid The new SSID to set.
     */
    void setSsid(QString const& ssid);

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

    /**
     * Returns the current brightness level.
     */
    float getBrightness() const {
        return m_brightness;
    }

    /**
     * Returns the current volume level.
     */
    float getVolume() const {
        return m_volume;
    }

    /**
     * Sets the brightness level.
     * @param value The brightness level to set.
     */
    void setBrightness(float value);

    /**
     * Sets the volume level.
     * @param value The volume level to set.
     */
    void setVolume(float value);

    /**
     * Returns the current volume type.
     */
    VolumeType::Level getVolumeType() const {
        return m_volumeType;
    }

    /**
     * Sets the volume type.
     * @param type The volume type to set.
     */
    void setVolumeType(VolumeType::Level type);

signals:
    void titleChanged();
    void networkStrengthChanged();
    void airplaneModeChanged();
    void lightModeChanged();
    void brightnessChanged();
    void volumeChanged();
    void volumeTypeChanged();
    void ssidChanged();

private:

    void updateNetworkStatus(NetworkStatusEvent const& event);

    NetworkServiceIfc& m_networkService;

    QString m_title;
    QString m_ssid;
    int32_t m_networkStrength; // -1 to 100, -1 means no network
    bool m_airplaneMode;
    bool m_lightMode;
    float m_brightness;
    float m_volume;
    VolumeType::Level m_volumeType;
};

#endif