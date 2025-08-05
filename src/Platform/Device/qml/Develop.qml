import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui
import Configuration


ColumnLayout {
    id: columnLayout
    anchors.fill: parent

    // TODO move to own settings page
    SettingGroup {
        id: developGroup1
        Layout.fillWidth: true

        title: qsTr("Appearance")

        SettingKeyValueItem {
            title: qsTr("Selected Theme")
            value: ThemeManager.isLightMode() ? qsTr("Light") : qsTr("Dark")
        }
        SettingKeySwitchItem {
            title: qsTr("Theme")
            onToggled: {
                ThemeManager.toggleTheme()
            }
        }
    }
}
