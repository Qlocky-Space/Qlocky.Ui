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
            title: qsTr("Number of Stations")
            value: viewModel.radios.rowCount()
        }
    }
}
