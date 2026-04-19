#ifndef ABOUT_VIEW_MODEL_H
#define ABOUT_VIEW_MODEL_H

#include <DeviceInfoProviderIfc.h>
#include <QDateTime>
#include <QElapsedTimer>
#include <QList>
#include <QlockyConfig.h>
#include <QObject>
#include <QString>
#include <QTimer>

#include "Mediator.h"
#include "NetInterfaceInfoViewModel.h"

class AboutViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString appVersion READ getAppVersion CONSTANT)
    Q_PROPERTY(QString appBuildNumber READ getAppBuildNumber CONSTANT)
    Q_PROPERTY(QString kernelVersion READ getKernelVersion CONSTANT)
    Q_PROPERTY(QString kernelBuildDate READ getKernelBuildDate CONSTANT)
    Q_PROPERTY(QString deviceModel READ getDeviceModel CONSTANT)
    Q_PROPERTY(QString serialNumber READ getSerialNumber CONSTANT)
    Q_PROPERTY(QString productName READ getProductName CONSTANT)

    Q_PROPERTY(QString hostname READ getHostname NOTIFY hostnameChanged)
    Q_PROPERTY(uint64_t upTime READ getUpTime NOTIFY upTimeChanged)
    Q_PROPERTY(QList<NetInterfaceInfoViewModel*> netInterfaceInfos READ getNetInterfaceInfos NOTIFY netInterfaceInfosChanged)

public:

    explicit AboutViewModel(Mediator& mediator, DeviceInfoProviderIfc& deviceInfo);
    ~AboutViewModel() final = default;

    /**
     * Returns the application version.
     */
    QString getAppVersion() const {
        return QLOCKY_APP_VERSION;
    }

    /**
     * Returns the product name of the application.
     */
    QString getProductName() const {
        return QLOCKY_APP_NAME;
    }

    /**
     * Returns the device operating system version.
     */
    QString getKernelVersion() const {
        return QString::fromStdString(m_deviceInfoProvider.getKernelVersion());
    }

    /**
     * Returns the kernel build date.
     */
    QString getKernelBuildDate() const {
        return QString::fromStdString(m_deviceInfoProvider.getKernelBuildDate());
    }

    /**
     * Returns the device model name.
     */
    QString getDeviceModel() const {
        return QString::fromStdString(m_deviceInfoProvider.getModelName());
    }

    /**
     * Returns the device name.
     */
    QString getDeviceName() const {
        return QString::fromStdString(m_deviceInfoProvider.getDeviceName());
    }

    /**
     * Returns the device serial number.
     */
    QString getSerialNumber() const {
        return QString::fromStdString(m_deviceInfoProvider.getSerialNumber());
    }

    /**
     * Returns the build number of the application.
     */
    QString getAppBuildNumber() const {
        return QLOCKY_APP_REVISION;
    }

    /**
     * Up time of the device.
     */
    uint64_t getUpTime() const {
        return m_upElapsedTimer.elapsed() / 1000; // Convert milliseconds to seconds
    }

    /**
     * Returns the hostname of the device.
     */
    QString getHostname() const {
        return QString::fromStdString(m_deviceInfoProvider.getHostname());
    }

    /**
     * Returns network interface information view models.
     */
    QList<NetInterfaceInfoViewModel*> getNetInterfaceInfos() const {
        return m_netInterfaceInfos;
    }

    /**
     * Changes the hostname of the device.
     * @param hostname The new hostname to set.
     */
    Q_INVOKABLE void changeHostname(QString const& hostname);

signals:

    void upTimeChanged();
    void hostnameChanged();
    void netInterfaceInfosChanged();

private:

    void refreshNetInterfaceInfos();

    DeviceInfoProviderIfc& m_deviceInfoProvider;
    QTimer m_upTimer;
    QElapsedTimer m_upElapsedTimer;
    QList<NetInterfaceInfoViewModel*> m_netInterfaceInfos;
};

#endif