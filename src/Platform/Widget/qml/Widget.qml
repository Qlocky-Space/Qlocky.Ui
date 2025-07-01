import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property color color: "transparent"

    Rectangle {
        anchors.fill: parent
        radius: 20
        color: root.color
    }
}
