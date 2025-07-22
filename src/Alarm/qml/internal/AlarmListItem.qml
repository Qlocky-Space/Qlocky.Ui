import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui
import Alarm

SwipeDelegate {
    id: root

    required property int alarmId
    property string displayName: "Label"
    property bool isEnabled: false
    property string time: "00:00"
    property bool isSnoozing: false
    property string dayOfWeek: ""

    signal activationToggled(bool isEnabled)

    contentItem: Item {
        implicitHeight: 132

        RowLayout {
            id: contentArea
            anchors.fill: parent
            anchors.margins: 16

            Column {
                QLabel {
                    text: root.time
                    font.pixelSize: 56
                }

                QLabel {
                    text: root.dayOfWeek
                    font.pixelSize: 32
                }
            }

            QLabel {
                text: root.isSnoozing ? qsTr("Snoozing") : ""
                Layout.fillWidth: true
            }

            QToggleButton {
                checked: root.isEnabled

                onToggled: function (state) {
                    root.isEnabled = state;
                    root.activationToggled(state);
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
                    CommandExecutor.dispatch("alarm-edit", {
                        "id": root.alarmId
                    });
                    root.swipe.close();
                }
            }

            AlarmSwipeButton {
                icon: "\uf1f8"
                color: ThemeManager.theme.red

                onClicked: {
                    root.swipe.close();
                    CommandExecutor.dispatch("alarm-remove", {
                        "id": root.alarmId
                    });
                    removeAnimation.start();
                }
            }
        }
    }

    background: Rectangle {
        color: root.isEnabled ? ThemeManager.theme.fillsPrimary : ThemeManager.theme.fillsQuaternary
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
