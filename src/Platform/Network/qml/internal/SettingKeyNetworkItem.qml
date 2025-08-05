import QtQuick
import QtQuick.Layouts

import Ui
import Configuration
import Network

SettingKeyValueBase {
    id: root

    property int strength
    property bool active

    QIcon {
        icon: NetworkIconUtil.toNetworkStrength(strength)
        color: root.titleColor
    }

    menu.contentData: [
        QMenuItem {
            text: qsTr("Forget")
            onTriggered: CommandExecutor.dispatch("network-forget", { "ssid": ssid })
        },
        QMenuItem {
            text: qsTr("Disconnect")
            onTriggered: CommandExecutor.dispatch("network-disconnect")
        }
    ]
}