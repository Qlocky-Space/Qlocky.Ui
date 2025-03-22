import QtQuick
import QtQuick.Layouts

import AppShell

Card {
    cardColor: "#202226"

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
            source: "/Weather/resources/sun.png"

            width: 40
            height: 40
        }

        Text {
            text: "Dienstag"
            font.pixelSize: 32
            color: "white"
        }
        Image {
            source: "/Weather/resources/cloudy.png"

            width: 40
            height: 40
        }

        Text {
            text: "Mittwoch"
            font.pixelSize: 32
            color: "white"
        }
        Image {
            source: "/Weather/resources/cloudy-sun-rain.png"

            width: 40
            height: 40
        }

        Text {
            text: "Donnerstag"
            font.pixelSize: 32
            color: "white"
        }
        Image {
            source: "/Weather/resources/snow.png"

            width: 40
            height: 40
        }
    }
}
