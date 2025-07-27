import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

RowLayout {
    anchors.leftMargin: 50
    anchors.rightMargin: 50

    height: 80


    property var viewModel: StatusBarViewModel

    Row {
        spacing: 30
        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

        QIcon {
            id: networkIcon

            visible: !viewModel.isAirplaneModeEnabled
            icon: IconUtil.toNetworkStrength(viewModel.networkState, viewModel.networkStrength)
        }

        QIcon {
            id: airplaneIcon

            visible: viewModel.isAirplaneModeEnabled
            icon: "\uf072"
        }

        QIcon {
            id: volumeIcon
            icon: IconUtil.toVolumeType(viewModel.volumeType, viewModel.volume)
        }
    }

    Item {
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

        QLabel {
            anchors.centerIn: parent
            color: titlebar.fontColor

            text: viewModel.title
        }
    }

    Row {
        spacing: 30
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

        QIcon {
            id: settingsIcon

            icon: "\uf013"
        }
    }
}