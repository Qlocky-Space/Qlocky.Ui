import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui
import Configuration


ColumnLayout {
    id: columnLayout
    anchors.fill: parent

    property var viewModel: RadioSettingsPageViewModel

    SettingGroup {
        id: generalGroup
        Layout.fillWidth: true

        title: qsTr("General")

        SettingKeyValueItem {
            title: qsTr("Stations")
            value: viewModel.stationCount

            additionalContent: QButton {
                id: scanButton
                buttonStyle: QButton.ButtonStyle.Plain
                image: "\uf021"
                onClicked: viewModel.updateStations()

                // Rotation animation while downloading
                RotationAnimator on rotation {
                    running: viewModel.downloading
                    from: 0
                    to: 360
                    duration: 800
                    loops: Animation.Infinite
                }
            }
        }
    }
}
