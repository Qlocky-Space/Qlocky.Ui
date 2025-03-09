import QtQuick

Item {
    id: titlebar
    width: parent.width
    height: 50

    Rectangle {
        anchors.fill: parent
        color: "#202226"

        Text {
            color: "white"

            text: "Sun, 9 März - 16:16"
            font.pointSize: 20
            anchors.rightMargin: 20

            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
        }
    }
}
