import QtQuick
import QtQuick.Layouts

import Ui
import Configuration
import Network

SettingKeyValueBase {
    id: root

    required property int signalStrength

    QIcon {
        icon: NetworkIconUtil.toNetworkStrength(signalStrength)
        color: root.titleColor
    }
}