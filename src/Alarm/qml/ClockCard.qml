import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Widget
import Ui

Widget {
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
            color: ThemeManager.theme.labelPrimary
        }
        Text {
            text: "16 : 16"
            font.family: digiFont.name
            font.pixelSize: 220
            font.bold: true
            color: ThemeManager.theme.labelPrimary
        }
    }

    RowLayout {
        QButton {
            text: "Console Print"

            enabled: ClockCardViewModel.pingCommand.canExecute
            onClicked: {
                ClockCardViewModel.pingCommand.execute();
            }
        }

        QButton {
            text: "Theme"
            image: "\uf1b9"

            onClicked: {
                ThemeManager.toggleTheme()
            }
        }

    }
}
