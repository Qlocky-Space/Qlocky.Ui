import QtQuick

Item {
    id: titlebar
    width: parent.width
    height: 50

    Rectangle {
        anchors.fill: parent
        color: "#202226"

        Item {
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            Image {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 30

                source: "/AppShell/resources/signal.png"
                height: 30
                width: 35
            }
        }

        Item {
            anchors.centerIn: parent

            Text {
                anchors.centerIn: parent

                color: "white"

                text: "Qlocky"
                font.pointSize: 20
            }
        }

        Item {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            Image {
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 30

                source: "/AppShell/resources/settings.png"
                height: 35
                width: 35
            }
        }
    }
}
