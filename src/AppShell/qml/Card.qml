import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property color cardColor

    Rectangle {
        anchors.fill: parent
        radius: 20
        color: root.cardColor
    }
}
