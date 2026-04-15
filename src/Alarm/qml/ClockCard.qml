import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui
import Alarm

QWidget {
    FontLoader {
        id: digiFont
        source: "/Alarm/resources/fonts/cour.ttf"
    }

    Grid {
        anchors.centerIn: parent

        columns: 1
        spacing: 10

        Text {
            text: TimeConverter.asDate(ClockCardViewModel.timestamp)
            font.pixelSize: 72
            color: ThemeManager.theme.labelPrimary
        }
        Text {
            text: TimeConverter.asTime(ClockCardViewModel.timestamp)
            font.family: digiFont.name
            font.pixelSize: 220
            font.bold: true
            color: ThemeManager.theme.labelPrimary
        }
    }
}
