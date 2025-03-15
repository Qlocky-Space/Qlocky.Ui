import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import ".."

Card {
    cardColor: "#202226"

    Layout.row: 2
    Layout.rowSpan: 1
    Layout.column: 2
    Layout.columnSpan: 3

    ScrollView {
        anchors.centerIn: parent
        anchors.fill: parent
        anchors.margins: 40

        Column {
            width: parent.width
            spacing: 10

            Text {
                text: "Line 1"
                font.pixelSize: 32
                color: "white"
            }
            Text {
                text: "Line 2"
                font.pixelSize: 32
                color: "white"
            }
            Text {
                text: "Line 3"
                font.pixelSize: 32
                color: "white"
            }
            Text {
                text: "Line 4"
                font.pixelSize: 32
                color: "white"
            }
            Text {
                text: "Line 5"
                font.pixelSize: 32
                color: "white"
            }
            Text {
                text: "Line 6"
                font.pixelSize: 32
                color: "white"
            }
        }
    }
}
