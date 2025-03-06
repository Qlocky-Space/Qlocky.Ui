import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    anchors.fill: parent
    spacing: 10

    Button {
        id: button
        text: "Example 10"
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop

        background: Rectangle {
            color: button.down ? "#173ebd" : "#3700ff"
            implicitWidth: 300
            implicitHeight: 80
        }
    }

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
