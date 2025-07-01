import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Widget
import Ui

Widget {
    id: card
    color: ThemeManager.theme.fillsSecondary

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
                text: qsTr("SongName")
                color: ThemeManager.theme.labelPrimary
                font.pixelSize: 32
            }

            Text {
                text: qsTr("AlbumName")
                color: ThemeManager.theme.labelPrimary
                font.pixelSize: 32
            }
        }
    }

    Column {
        id: radio

        anchors.top: metadata.bottom
        anchors.topMargin: 110
        anchors.horizontalCenter: parent.horizontalCenter

        function formatTime(ms) {
            let totalSeconds = Math.floor(ms / 1000);
            let minutes = Math.floor(totalSeconds / 60);
            let seconds = totalSeconds % 60;

            return (minutes < 10 ? "0" : "") + minutes + ":" + (seconds < 10 ? "0" : "") + seconds;
        }

        Slider {
            id: slider
            orientation: Qt.Horizontal
            from: 0
            to: 100
            value: 40
            width: card.width * 0.7
            snapMode: Slider.NoSnap
            height: 20

            anchors.centerIn: radio
        }

        Text {
            anchors.top: slider.bottom
            anchors.left: slider.left
            text: radio.formatTime(slider.value / 100 * 221000)
            color: ThemeManager.theme.labelPrimary
            font.pixelSize: 24
        }

        Text {
            anchors.top: slider.bottom
            anchors.right: slider.right
            text: radio.formatTime((100 - slider.value) / 100 * 221000)
            color: ThemeManager.theme.labelPrimary
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
        }

        Image {
            source: "/Radio/resources/skip.png"

            width: 80
            height: 80
        }
    }
}
