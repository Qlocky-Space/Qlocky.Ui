import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

SwipeDelegate {
    id: root

    property bool active: false

    property string time: "00:00"

    ListView.onRemove: removeAnimation.start()

    contentItem: Item {
        implicitHeight: 132

        RowLayout {
            id: contentArea
            anchors.fill: parent
            anchors.margins: 16

            QLabel {
                text: root.time
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
    }

    swipe.right: Loader {
        id: swipArea
        width: 300
        active: root.swipe.complete || root.pressed

        height: parent.height
        anchors.right: parent.right

        sourceComponent: RowLayout {
            anchors.fill: parent
            spacing: 0

            AlarmSwipeButton {
                icon: "\uf304"
                color: ThemeManager.theme.orange

                onClicked: {
                    // TOOD CommandExecutor.dispatch("alarm-edit", root.alarmId)
                    console.log("Edit Clicked")

                    CommandExecutor.dispatch("nav-to", {
                        "uri": "qlocky://newAlarmDialog?text=Edit Alarm"
                    });
                }
            }

            AlarmSwipeButton {
                icon: "\uf1f8"
                color: ThemeManager.theme.red

                onClicked: {
                    // TOOD CommandExecutor.dispatch("alarm-remove", root.alarmId)
                    console.log("Remove Clicked")
                }
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