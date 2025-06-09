import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: titlebar
    width: parent.width

    Rectangle {
        id: statusBar
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

        MouseArea {
            id: swipeArea
            anchors.fill: parent
            drag.target: overlay
            drag.axis: Drag.YAxis
            drag.minimumY: -overlay.height
            drag.maximumY: 0

            onReleased: {
                if (overlay.y > -(overlay.height - titlebar.height)) {
                    overlay.y = 0;
                } else {
                    overlay.y = -overlay.height;
                }
            }
        }
    }

    Rectangle {
        id: overlay
        width: parent.width
        height: 1080
        color: "#303030"
        y: -height

        Behavior on y {
            NumberAnimation {
                duration: 200
            }
        }

        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            anchors.margins: 20

            // TODO extract into sepearte component and may replace it with a Drawer?
            Text {
                text: "Not impelemented yet"
                color: "white"
                font.pointSize: 16
                Layout.alignment: Qt.AlignHCenter
            }
        }

        MouseArea {
            id: overlaySwipeArea
            anchors.fill: parent
            drag.target: overlay
            drag.axis: Drag.YAxis
            drag.minimumY: -overlay.height
            drag.maximumY: 0

            onReleased: {
                if (overlay.y < -overlay.height / 3) {
                    overlay.y = -overlay.height;
                } else {
                    overlay.y = 0;
                }
            }
        }
    }
}
