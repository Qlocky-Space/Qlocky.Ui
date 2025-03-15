import QtQuick
import QtQuick.Layouts

import ".."

Card {
    cardColor: "#202226"

    Layout.row: 2
    Layout.rowSpan: 1
    Layout.column: 0
    Layout.columnSpan: 1

    Grid {
        anchors.centerIn: parent

        columns: 2
        spacing: 20

        Text {
            text: "Montag"
            font.pixelSize: 32
            color: "white"
        }
        Image {
            source: "/AppShell/resources/sun.png"

            width: 40
            height: 40
        }

        Text {
            text: "Dienstag"
            font.pixelSize: 32
            color: "white"
        }
        Image {
            source: "/AppShell/resources/cloudy.png"

            width: 40
            height: 40
        }

        Text {
            text: "Mittwoch"
            font.pixelSize: 32
            color: "white"
        }
        Image {
            source: "/AppShell/resources/cloudy-sun-rain.png"

            width: 40
            height: 40
        }

        Text {
            text: "Donnerstag"
            font.pixelSize: 32
            color: "white"
        }
        Image {
            source: "/AppShell/resources/snow.png"

            width: 40
            height: 40
        }
    }
}
