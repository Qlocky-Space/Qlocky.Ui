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

        SettingKeySwitchItem {
            title: qsTr("24-Hours")
            value: AppearanceViewModel.timeFormatBoolean
            onToggled: function (checked) {
                AppearanceViewModel.changeTimeFormat(checked);
            }
        }

        SettingKeyValueItem {
            title: qsTr("Time Zone")
            value: AppearanceViewModel.timeZoneLabel
            clickable: true
            onClicked: CommandExecutor.dispatch("nav-to", {
                "uri": "qlocky://timeZoneSelectDialog"
            })
        }
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
