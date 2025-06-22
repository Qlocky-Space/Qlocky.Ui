import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Widget

Card {
    cardColor: "#202226"

    FontLoader {
        id: digiFont
        source: "/Alarm/resources/fonts/DS-DIGI.TTF"
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

    Button {
        text: "Demo"
        enabled: ClockCardViewModel.pingCommand.canExecute
        onClicked: {
            ClockCardViewModel.pingCommand.execute();
        }
    }
}
