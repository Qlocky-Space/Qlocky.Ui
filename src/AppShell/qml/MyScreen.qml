import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Alarm

RowLayout {
    anchors.fill: parent
    spacing: 10

    Alarm {}

    Button {
        id: button1
        Layout.alignment: Qt.AlignRight | Qt.AlignTop
        text: "Example 2"

        background: Rectangle {
            implicitWidth: 250
            implicitHeight: 80

            color: button1.down ? "#089969" : "#990808"
        }
    }
}
