import QtQuick 2.7


// The rounded rectangle works mostly like a regular rectangle, but provides the option to have rounded corners on only one side of the rectangle.
Item {
    id: roundedRectangle

    property color color: "transparent"
    property int radius: 24

    property int cornerSide: QRoundedRectangle.Direction.None

    property real borderWidth: 0
    property color borderColor: "transparent"

    enum Direction {
        None = 0,
        Down = 1,
        Left = 2,
        Up = 3,
        Right = 4,
        All = 5
    }

    Rectangle {
        id: background
        anchors.fill: parent
        radius: cornerSide != QRoundedRectangle.Direction.None ? parent.radius : 0
        color: parent.color
        border.width: parent.borderWidth
        border.color: parent.borderColor
    }

    // The item that covers 2 of the corners to make them not rounded.
    Rectangle {
        visible: cornerSide != QRoundedRectangle.Direction.None && cornerSide != QRoundedRectangle.Direction.All
        height: cornerSide % 2 ? parent.radius: parent.height
        width: cornerSide % 2 ? parent.width : parent.radius
        color: parent.color
        anchors {
            right: cornerSide == QRoundedRectangle.Direction.Left ? parent.right: undefined
            bottom: cornerSide == QRoundedRectangle.Direction.Up ? parent.bottom: undefined
        }

        border.width: parent.borderWidth
        border.color: parent.borderColor

        Rectangle {
            color: roundedRectangle.color
            height: cornerSide % 2 ? roundedRectangle.borderWidth: roundedRectangle.height - 2 * roundedRectangle.borderWidth
            width: cornerSide % 2 ? roundedRectangle.width - 2 * roundedRectangle.borderWidth: roundedRectangle.borderWidth
            anchors {
                right: cornerSide == QRoundedRectangle.Direction.Right ? parent.right : undefined
                bottom: cornerSide  == QRoundedRectangle.Direction.Down ? parent.bottom: undefined
                horizontalCenter: cornerSide % 2 ? parent.horizontalCenter: undefined
                verticalCenter: cornerSide % 2 ? undefined: parent.verticalCenter
            }
        }
    }
}