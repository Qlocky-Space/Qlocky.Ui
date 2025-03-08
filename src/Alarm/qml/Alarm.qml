import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

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
