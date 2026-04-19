#include "AboutViewModel.h"

#include <QStringList>
#include <string>

AboutViewModel::AboutViewModel(Mediator& mediator, DeviceInfoProviderIfc& deviceInfo) :
    m_deviceInfoProvider {deviceInfo},
    m_upTimer {this},
    m_upElapsedTimer {},
    m_netInterfaceInfos {} {
    m_upElapsedTimer.start();

    connect(&m_upTimer, &QTimer::timeout, this, [this]() {
        emit upTimeChanged();

        // Refresh network info every 10 seconds
        if ((getUpTime() % 10) == 0) {
            refreshNetInterfaceInfos();
        }
    });
    m_upTimer.setInterval(1000); // Update every second
    m_upTimer.start();
}

void AboutViewModel::changeHostname(QString const& hostname) {
    if (hostname.isEmpty()) {
        qWarning("Hostname cannot be empty.");
        return;
    }

    m_deviceInfoProvider.setHostname(hostname.toStdString());
    emit hostnameChanged();
}

void AboutViewModel::refreshNetInterfaceInfos() {
    // Build a map of existing viewmodels by interface name
    QMap<QString, NetInterfaceInfoViewModel*> existingMap;
    for (auto const& ptr : m_netInterfaceInfos) {
        if (ptr) {
            existingMap[ptr->getInterfaceName()] = ptr;
        }
    }

    std::vector<NetInterfaceInfo> infos {m_deviceInfoProvider.getNetInterfaceInfos()};
    QList<NetInterfaceInfoViewModel*> newList {};

    for (NetInterfaceInfo const& info : infos) {
        if (info.Name.empty()) {
            continue;
        }
        QString name = QString::fromStdString(info.Name);
        QStringList addresses;
        for (std::string const& address : info.IpAddresses) {
            if (!address.empty()) {
                addresses.append(QString::fromStdString(address));
            }
        }
        QString ipText = addresses.isEmpty() ? QStringLiteral("-") : addresses.join(QStringLiteral(", "));
        QString macText = info.MacAddress.empty() ? QStringLiteral("-") : QString::fromStdString(info.MacAddress);

        if (existingMap.contains(name)) {
            auto& vm = existingMap[name];
            vm->setIpAddresses(ipText);
            vm->setMacAddress(macText);
            vm->setIsUp(info.IsUp);
            newList.append(vm);
        }
        else {
            newList.append(new NetInterfaceInfoViewModel(
                this,
                name,
                ipText,
                macText,
                info.IsUp));
        }
    }

    if (newList != m_netInterfaceInfos) {
        m_netInterfaceInfos = newList;
        emit netInterfaceInfosChanged();
    }
}