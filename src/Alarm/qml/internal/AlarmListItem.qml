import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

SwipeDelegate {
    id: root

    property bool active: false


    ListView.onRemove: removeAnimation.start()

    contentItem: Item {
        implicitHeight: 132

        RowLayout {
            id: contentArea
            anchors.fill: parent
            anchors.margins: 16

            QLabel {
                text: "6:20"
            }

            QLabel {
                text: "Imgs"
                Layout.fillWidth: true
            }

            QToggleButton {
                checked: root.active

                onToggled: function(state) {
                    root.active = state
                }
            }
        }

        // TODO doesn't work
        TapHandler {
            onTapped: {
                root.active = !root.active
            }

            onLongPressed: {
                CommandExecutor.dispatch("nav-to", {
                        "uri": "qlocky://newAlarmDialog?text=Edit Alarm"
                });
            }

            // prevent conflict with swiping
            gesturePolicy: TapHandler.DragThreshold  // allows drag gestures to pass
            grabPermissions: TapHandler.CanTakeOverFromAnything
            longPressThreshold: 0.4
        }
    }

    swipe.right: Loader {
        id: swipArea
        width: 150
        active: root.swipe.complete || root.pressed

        height: parent.height
        anchors.right: parent.right

        sourceComponent: Item {
            anchors.fill: parent

            Rectangle {
                anchors.fill: parent
                color: "red"
            }

            QIcon {
                anchors.centerIn: parent
                size: 48
                icon: "\uf1f8"
            }

            SwipeDelegate.onClicked: {
                console.log("Remove Clicked")
                root.swipe.close()
            }
        }

    }

    background: Rectangle {
        color: root.active ? ThemeManager.theme.fillsPrimary : ThemeManager.theme.fillsQuaternary
    }

    SequentialAnimation {
        id: removeAnimation

        PropertyAction {
            target: root
            property: "ListView.delayRemove"
            value: true
        }
        NumberAnimation {
            target: root
            property: "height"
            to: 0
            easing.type: Easing.InOutQuad
        }
        PropertyAction {
            target: root
            property: "ListView.delayRemove"
            value: false
        }
    }
}