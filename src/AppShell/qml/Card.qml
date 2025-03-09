import QtQuick
import QtQuick.Layouts

Item {
    id: root
    width: 365 * columns
    height: 250 * rows

    property color cardColor
    property int rows
    property int columns

    Rectangle {
        anchors.fill: parent
        radius: 20
        color: root.cardColor
    }
}
