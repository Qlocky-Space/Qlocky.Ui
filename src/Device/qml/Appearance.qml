import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui
import Configuration
import Device

ColumnLayout {
    id: columnLayout
    anchors.fill: parent

    SettingGroup {
        id: internationalGroup
        Layout.fillWidth: true

        title: qsTr("International")
    }

    SettingGroup {
        id: themeGroup
        Layout.fillWidth: true

        title: qsTr("Theme")

        SettingKeyValueItem {
            title: qsTr("Selected Theme")
            value: ThemeManager.isLightMode() ? qsTr("Light") : qsTr("Dark")
        }
        SettingKeySwitchItem {
            title: qsTr("Theme")
            onToggled: {
                ThemeManager.toggleTheme();
            }
        }
    }
}
