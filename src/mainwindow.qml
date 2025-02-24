import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    visible: true
    color: 'black'

    // TODO: Move this to c++
    Component.onCompleted: {
         root.showFullScreen();
    }

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Button {
            id: button
            text: "Example 10"
            anchors.top: parent.top
            anchors.left: parent.left

            background: Rectangle {
                color:  button.down ? "#173ebd" : "#3700ff"
                implicitWidth: 300
                implicitHeight: 80
            }
        }

        Button {
            id: button1
            anchors.top: parent.top
            anchors.right: parent.right
            text: "Example 2"

            background: Rectangle {
                implicitWidth: 250
                implicitHeight: 80

                color:  button1.down ? "#089969" : "#990808"
            }
        }
    }
}
