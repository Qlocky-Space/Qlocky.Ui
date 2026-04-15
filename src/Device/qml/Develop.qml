import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui
import Configuration
import Device


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

    SettingGroup {
        id: lifecycleGroup
        Layout.fillWidth: true

        title: qsTr("Application Lifecycle")

        SettingKeyValueItem {
            title: qsTr("Actual State")
            value: {
                switch (DevelopViewModel.lifecycleState) {
                    case LifecycleStateType.Startup:  return qsTr("Startup")
                    case LifecycleStateType.Active:   return qsTr("Active")
                    case LifecycleStateType.Inactive: return qsTr("Inactive")
                    case LifecycleStateType.Suspend:  return qsTr("Suspend")
                    case LifecycleStateType.Shutdown: return qsTr("Shutdown")
                    default:                          return qsTr("Unknown")
                }
            }
        }

        SettingKeyButtonItem {
            title: qsTr("Request Inactive State")
            text: qsTr("Perform")

            onClicked: {
                CommandExecutor.dispatch("lifecycleChangeRequest", { state: "Inactive" });
            }
        }
    }
}
