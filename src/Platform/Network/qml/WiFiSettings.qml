import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui
import Configuration


ColumnLayout {
    id: columnLayout
    anchors.fill: parent

    // TODO implement Wi-Fi settings
    SettingGroup {
        id: developGroup1
        Layout.fillWidth: true

        title: qsTr("Wi-Fi Settings")

        SettingKeySwitchItem {
            id: wifiSwitch
            title: qsTr("Wi-Fi")
        }

        Repeater {
            model: ["WLAN1", "WLAN2", "WLAN3"]
            delegate: SettingKeyValueItem {
                required property string modelData

                title: modelData
                value: "TODO"
            }
        }
    }
}
