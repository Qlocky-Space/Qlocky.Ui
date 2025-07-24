import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    property var viewModel: StatusBarViewModel

    implicitHeight: 950
    implicitWidth: 1100

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 60

        Row {
            spacing: 48
            Layout.alignment: Qt.AlignRight | Qt.AlignTop

            QStatusBarAction {
                icon: "\uf023"
                onClicked: ThemeManager.toggleTheme()
            }

            QStatusBarAction {
                icon: "\uf011"
                onClicked: console.log("Shutdown clicked")
            }

            QStatusBarAction {
                icon: "\uf013"
                onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://settings" })
            }
        }

        RowLayout {
            QStatusBarGroup {
                Layout.fillWidth: true

                QStatusBarIcon {
                    isActive: viewModel.networkStrength > 0
                    icon: IconUtil.toIcon(viewModel.networkStrength)
                    iconInactive: "\uf6ac"
                    onClicked: function(state) {
                        viewModel.setNetworkState(state)
                    }
                    title: "Network long"
                    description: "Network status"
                }
            }

            QStatusBarGroup {
                QStatusBarIcon {
                    icon: "\uf072"
                    isActive: viewModel.isAirplaneModeEnabled
                    onClicked: function(state) {
                        viewModel.isAirplaneModeEnabled = state
                    }
                }

                QStatusBarIcon {
                    icon: "\uf0eb"
                    isActive: viewModel.lightMode
                    onClicked: function(state) {
                        viewModel.lightMode = state
                    }
                }
            }
        }

        QStatusBarGroup {
            QStatusBarIcon {
                icon: "\uf0e8"
                onClicked: console.log("Battery clicked")
                title: "Battery"
                description: "Battery status"
            }

            QStatusBarIcon {
                icon: "\uf2b9"
                onClicked: console.log("Bluetooth clicked")
                title: "Bluetooth"
            }

            QStatusBarIcon {
                icon: "\uf1eb"
                onClicked: console.log("Wi-Fi clicked")
                title: "Wi-Fi"
            }
        }
    }

    QHomeIndicator {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -30 // must be negative to be outside, so status overlay popup is closed
    }
}