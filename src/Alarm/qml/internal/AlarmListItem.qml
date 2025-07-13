import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui
import Alarm

SwipeDelegate {
    id: root

    required property AlarmListItemModel model

    contentItem: Item {
        implicitHeight: 132

        RowLayout {
            id: contentArea
            anchors.fill: parent
            anchors.margins: 16

            Column {
                QLabel {
                    // TODO Use 24HFormat configuration from Persistency
                    text: Qt.formatDateTime(root.model.time, "HH:mm")
                    font.pixelSize: 56
                }

                QLabel {
                    text: root.model.label
                    font.pixelSize: 32
                }
            }

            QLabel {
                text: ""
                Layout.fillWidth: true
            }

            QToggleButton {
                checked: root.model.active

                onToggled: function(state) {
                    root.model.active = state
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
                    console.log("Edit Clicked")

                    // TOOD CommandExecutor.dispatch("alarm-edit", root.alarmId)
                    CommandExecutor.dispatch("nav-to", {
                        "uri": "qlocky://newAlarmDialog?text=Edit Alarm"
                    });

                    root.swipe.close()
                }
            }

            AlarmSwipeButton {
                icon: "\uf1f8"
                color: ThemeManager.theme.red

                onClicked: {
                    root.swipe.close()

                    console.log("Remove Clicked")
                    removeAnimation.start()

                    // TOOD CommandExecutor.dispatch("alarm-remove", root.alarmId)
                }
            }
        }

    }

    background: Rectangle {
        color: root.model.active ? ThemeManager.theme.fillsPrimary : ThemeManager.theme.fillsQuaternary
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
            property: "visible"
            value: false
        }
        PropertyAction {
            target: root
            property: "ListView.delayRemove"
            value: false
        }
    }
}