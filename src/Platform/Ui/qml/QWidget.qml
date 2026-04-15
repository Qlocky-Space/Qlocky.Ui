import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property color color: "transparent"
    property real radius: 24

    Rectangle {
        anchors.fill: parent
        radius: root.radius
        color: root.color
    }
}
