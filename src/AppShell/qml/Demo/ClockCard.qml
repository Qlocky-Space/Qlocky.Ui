import QtQuick
import QtQuick.Layouts

import ".."

Card {
    cardColor: "#202226"

    Layout.row: 0
    Layout.rowSpan: 2
    Layout.column: 2
    Layout.columnSpan: 3

    FontLoader {
        id: digiFont
        source: "/AppShell/resources/fonts/DS-DIGI.TTF"
    }

    Grid {
        anchors.centerIn: parent

        columns: 1
        spacing: 10

        Text {
            text: "Sonntag, 9. März 2025"
            font.pixelSize: 72
            color: "white"
        }
        Text {
            text: "16 : 16"
            font.family: digiFont.name
            font.pixelSize: 220
            font.bold: true
            color: "white"
        }
    }
}
