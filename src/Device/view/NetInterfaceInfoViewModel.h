#ifndef NET_INTERFACE_INFO_VIEW_MODEL_H
#define NET_INTERFACE_INFO_VIEW_MODEL_H

#include <QObject>
#include <QString>
#include <utility>

/**
 * View model representing a single network interface.
 */
class NetInterfaceInfoViewModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString interfaceName READ getInterfaceName CONSTANT)
    Q_PROPERTY(QString ipAddresses READ getIpAddresses WRITE setIpAddresses NOTIFY ipAddressesChanged)
    Q_PROPERTY(QString macAddress READ getMacAddress WRITE setMacAddress NOTIFY macAddressChanged)
    Q_PROPERTY(bool isUp READ isUp WRITE setIsUp NOTIFY isUpChanged)

public:

    NetInterfaceInfoViewModel(QObject* parent, QString interfaceName, QString ipAddresses, QString macAddress, bool isUp) :
        QObject {parent},
        m_interfaceName {std::move(interfaceName)},
        m_ipAddresses {std::move(ipAddresses)},
        m_macAddress {std::move(macAddress)},
        m_isUp {isUp} {
    }

    QString getInterfaceName() const {
        return m_interfaceName;
    }

    QString getIpAddresses() const {
        return m_ipAddresses;
    }
    void setIpAddresses(QString const& ipAddresses) {
        if (m_ipAddresses != ipAddresses) {
            m_ipAddresses = ipAddresses;
            emit ipAddressesChanged();
        }
    }

    QString getMacAddress() const {
        return m_macAddress;
    }
    void setMacAddress(QString const& macAddress) {
        if (m_macAddress != macAddress) {
            m_macAddress = macAddress;
            emit macAddressChanged();
        }
    }

    bool isUp() const {
        return m_isUp;
    }
    void setIsUp(bool isUp) {
        if (m_isUp != isUp) {
            m_isUp = isUp;
            emit isUpChanged();
        }
    }

signals:
    void ipAddressesChanged();
    void macAddressChanged();
    void isUpChanged();

private:

    QString m_interfaceName;
    QString m_ipAddresses;
    QString m_macAddress;
    bool m_isUp;
};

#endif
