import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root
    anchors.fill: parent

    property var viewModel: SettingPageViewModel

    Component.onCompleted: {
        viewModel.selectedIndex = 0;
    }

    RowLayout {
        anchors.fill: parent

        // Left Column
        Item {
            width: 790
            Layout.fillHeight: true

            Rectangle {
                anchors.fill: parent
                color: ThemeManager.theme.backgroundSecondary
            }

            RowLayout {
                id: header
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top

                    margins: 50
                }

                QButton {
                    id: backButton
                    buttonStyle: QButton.ButtonStyle.Plain
                    image: "\uf060"
                    imageSize: 72

                    onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://main" })
                }

                QLabel {
                    Layout.fillWidth: true

                    text: qsTr("Settings")
                    font: FontStyle.h1
                    horizontalAlignment: Text.AlignHCenter | Text.AlignLeft
                }
            }

            SettingMenu {
                model: viewModel.items
                selectedIndex: viewModel.selectedIndex

                anchors {
                    left: parent.left
                    right: parent.right
                    top: header.bottom
                    bottom: parent.bottom
                }

                onSettingSelected: function(index) {
                    root.viewModel.selectedIndex = index
                }
            }
        }

        // Right Column
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            color: ThemeManager.theme.backgroundPrimary

            ColumnLayout {
                id: content
                anchors.fill: parent
                anchors.margins: 50

                Item {
                    Layout.alignment: Qt.AlignTop
                    Layout.preferredHeight: 80

                    QLabel {
                        text: viewModel.currentPageTitle
                        font: FontStyle.h1
                    }
                }

                Item {
                    Layout.alignment: Qt.AlignTop
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Loader {
                        id: contentLoader
                        anchors.fill: parent
                        source: viewModel.currentPageComponent
                    }
                }
            }
        }
    }
}
