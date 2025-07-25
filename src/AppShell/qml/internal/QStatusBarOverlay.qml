import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    property var viewModel: StatusBarViewModel

    ColumnLayout {
        spacing: 20

        anchors.top: parent.top

        implicitHeight: 850
        implicitWidth: 1100

        Row {
            spacing: 48
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.bottomMargin: 30

            QStatusBarAction {
                image: "\uf023"
                onClicked: console.log("Lock clicked")
            }

            QStatusBarAction {
                image: "\uf011"
                onClicked: console.log("Shutdown clicked")
            }

            QStatusBarAction {
                image: "\uf013"
                onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://settings" })
            }
        }

        RowLayout {
            QStatusBarGroup {
                Layout.fillWidth: true

                QStatusBarIcon {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    Layout.fillWidth: true

                    isActive: viewModel.networkStrength > 0
                    image: IconUtil.toNetworkStrength(viewModel.networkStrength)
                    imageInactive: "\uf6ac"
                    onClicked: function(state) {
                        viewModel.setNetworkState(state)
                    }
                    title: qsTr("WLAN")
                    description: viewModel.ssid
                }
            }

            QStatusBarGroup {
                QStatusBarIcon {
                    image: "\uf072"
                    isActive: viewModel.isAirplaneModeEnabled
                    onClicked: function(state) {
                        viewModel.isAirplaneModeEnabled = state
                    }
                }

                QStatusBarIcon {
                    image: "\uf0eb"
                    isActive: viewModel.lightMode
                    onClicked: function(state) {
                        viewModel.lightMode = state
                    }
                }
            }
        }

        QStatusBarGroup {
            rowMode: false
            Layout.fillWidth: true
            spacing: 32

            QStatusBarSliderWithButton {
                sliderImage:  IconUtil.toVolume(viewModel.volume)
                image: IconUtil.toVolumeType(viewModel.volumeType, viewModel.volume)
                status: IconUtil.toVolumeTypeStatus(viewModel.volumeType)
                value: viewModel.volume

                onClicked: {
                    switch (viewModel.volumeType) {
                        case VolumeType.Mute:
                            viewModel.volumeType = VolumeType.Vibration;
                            break;
                        case VolumeType.Vibration:
                            viewModel.volumeType = VolumeType.Acoustic;
                            break;
                        case VolumeType.Acoustic:
                            viewModel.volumeType = VolumeType.Mute;
                            break;
                    }
                }
                onValueUpdated: function(value) {
                    viewModel.volume = value;
                }
            }

            QStatusBarSliderWithButton {
                id: brightnessSlider
                sliderImage: "\ue0c9"
                image: "\ue0c9"
                imageInactive: "\uf186"
                status: ThemeManager.isLightMode()
                value: viewModel.brightness
                onClicked: {
                    ThemeManager.toggleTheme()
                }
                onValueUpdated: function(value) {
                    viewModel.brightness = value;
                }
            }
        }
    }
}