import QtQuick
import QtQuick.Layouts

import ".."

Card {
    cardColor: "#202226"

    Layout.row: 0
    Layout.rowSpan: 2
    Layout.column: 0
    Layout.columnSpan: 2

    Image {
        source: "/AppShell/resources/cloudy-sun.png"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50
        width: 300
        height: 300
    }

    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60

        columns: 2
        spacing: 10

        Text {
            text: "Bütschwil (SG)"
            font.pixelSize: 36
            font.bold: true
            color: "white"
        }
        Text {
            text: " "
            font.pixelSize: 36
            color: "white"
        }

        Text {
            text: "23°"
            font.pixelSize: 72
            color: "white"
        }
        Text {
            text: "-2° / 23°"
            font.pixelSize: 72
            color: "white"
        }

        Text {
            text: "Provided by manuel DEMO"
            font.pixelSize: 14
            font.italic: true
            color: "white"
        }
    }
}
