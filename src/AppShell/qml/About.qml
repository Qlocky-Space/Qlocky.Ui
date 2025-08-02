import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui
import Configuration


ColumnLayout {
    anchors.fill: parent

    SettingGroup {
        id: productGroup
        Layout.fillWidth: true

        title: qsTr("Product")

        SettingKeyValueItem {
            title: qsTr("Product Name")
            value: "Qlocky Device"
        }
        SettingKeyValueItem {
            title: qsTr("Model")
            value: "QL-A100"
        }
        SettingKeyValueItem {
            title: qsTr("Serial Number")
            value: "QL-123456"
        }
    }

    SettingGroup {
        id: legalRightsGroup
        Layout.fillWidth: true

        title: qsTr("Legal and regulatory")

        SettingKeyValueItem {
            title: qsTr("Third-party licences")
        }
        SettingKeyValueItem {
            title: qsTr("Source code")
            value: "TODO"
        }
    }

    SettingGroup {
        id: deviceIndentificationGroup
        Layout.fillWidth: true

        title: qsTr("Device identifiers")

        SettingKeyValueItem {
            title: qsTr("Uptime")
            value: "TODO"
        }
        SettingKeyValueItem {
            title: qsTr("Build number")
            value: "TODO"
        }
    }
}