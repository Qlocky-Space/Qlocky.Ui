import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui
import Configuration


ColumnLayout {
    id: columnLayout
    anchors.fill: parent

    property var viewModel: WiFiSettingsPageViewModel

    SettingGroup {
        id: developGroup1
        Layout.fillWidth: true

        title: qsTr("Networks")

        SettingKeySwitchItem {
            id: wifiSwitch
            title: qsTr("Wi-Fi")

            value: viewModel.wifiEnabled
            onToggled: function(value) {
                viewModel.wifiEnabled = value
            }

            additionalContent: QButton {
                id: scanButton
                buttonStyle: QButton.ButtonStyle.Plain
                image: "\uf021"
                onClicked: viewModel.startScan()

                // Rotation animation while scanning
                RotationAnimator on rotation {
                    running: viewModel.scanning
                    from: 0
                    to: 360
                    duration: 800
                    loops: Animation.Infinite
                }
            }
        }

        Repeater {
            model: viewModel.networks

            delegate: SettingKeyNetworkItem {
            }
        }
    }
}
