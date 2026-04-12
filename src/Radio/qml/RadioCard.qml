import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Widget
import Ui

Widget {
    id: card
    color: ThemeManager.theme.fillsSecondary

    property var viewModel: RadioCardViewModel

    QButton {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 20
        anchors.rightMargin: 20

        text: qsTr("Source")

        onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://radioSourceSelectDialog" })
    }

    Row {
        id: metadata
        spacing: 10
        anchors.top: card.top
        anchors.topMargin: 30

        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            color: "#5197de"
            width: 70
            height: 70

            anchors.right: infos.left
            anchors.rightMargin: 25
        }

        Column {
            id: infos

            Text {
                text: viewModel.title
                color: ThemeManager.theme.labelPrimary
                font.pixelSize: 32
            }

            Text {
                text: viewModel.subtitle
                color: ThemeManager.theme.labelPrimary
                font.pixelSize: 32
            }
        }
    }

    Column {
        id: radio

        anchors.top: metadata.bottom
        anchors.topMargin: 90
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 18

        Rectangle {
            width: card.width * 0.7
            height: 8
            radius: height / 2
            color: ThemeManager.theme.fillsTertiary

            Rectangle {
                width: viewModel.playing ? parent.width : parent.width * 0.2
                height: parent.height
                radius: parent.radius
                color: ThemeManager.theme.fillsPrimary
            }
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: viewModel.playing ? qsTr("Playing") : qsTr("Ready")
            color: ThemeManager.theme.labelSecondary
            font.pixelSize: 24
        }
    }

    Row {
        id: controls
        spacing: 10

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: radio.bottom
        anchors.topMargin: 30

        // TODO replace images with font awesome
        Image {
            source: "/Radio/resources/previous.png"

            width: 80
            height: 80
        }

        Image {
            source: "/Radio/resources/play.png"

            width: 80
            height: 80
            opacity: viewModel.hasRadio ? 1.0 : 0.4

            MouseArea {
                anchors.fill: parent
                enabled: viewModel.hasRadio
                cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor

                onClicked: {
                    viewModel.togglePlayback();
                }
            }
        }

        Image {
            source: "/Radio/resources/skip.png"

            width: 80
            height: 80
        }
    }
}
