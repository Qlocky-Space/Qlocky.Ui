import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui

Item {
    id: root
    anchors.fill: parent

    property var viewModel: SettingPageViewModel

    RowLayout {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        QButton {
            image: "\uf1b9"
            text: "Back"

            onClicked: {
                CommandExecutor.dispatch("nav-to", {
                    "uri": "qlocky://main"
                })
            }
        }

        QButton {
            text: "Theme"
            image: "\uf1b9"

            onClicked: {
                ThemeManager.toggleTheme()
            }
        }

        ColumnLayout {
            QButton {
                text: "Connect Network"

                onClicked: viewModel.networkConnect()
            }

            QButton {
                text: "Disconnect Network"

                onClicked: viewModel.networkDisconnect()
            }
        }

        QLabel {
            text: "Settings"
        }
    }
}
