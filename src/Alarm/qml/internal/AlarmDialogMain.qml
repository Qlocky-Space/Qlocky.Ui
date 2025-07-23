import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    required property var alarm

    implicitHeight: content.implicitHeight
    implicitWidth: content.implicitWidth

    signal showComponent(Component component)
    signal done()

    Column {
        id: content
        anchors.fill: parent
        spacing: 15

        QTimePicker {
            id: timePicker
            time: TimeConverter.utcToRelativeTime(alarm.dueTime)
            width: root.implicitWidth

            anchors.topMargin: 50
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.left: parent.left

            onClicked: function(time) {
                alarm.dueTime = TimeConverter.relativeTimeToUtc(time)
            }
        }

        AlarmDialogProperty {
            id: activeStatus

            anchors.left: parent.left
            anchors.right: parent.right

            status: alarm.state
            text: "Active"
            image: "\uf00c"

            trailing: QToggleButton {
                checked: alarm.state

                onToggled: function (state) {
                    alarm.state = state;
                }
            }
        }


        AlarmDialogProperty {
            id: repeatedStatus
            anchors.left: parent.left
            anchors.right: parent.right

            status: alarm.daysOfWeek !== DayOfWeek.None
            text: "Repeat"
            image: "\uf363"

            trailing: Row {
                spacing: 10
                QLabel {
                    text: AlarmDayUtils.getDaysDisplay(alarm.daysOfWeek)
                    color: ThemeManager.theme.labelSecondary
                    anchors.verticalCenter: parent.verticalCenter
                }

                QIcon {
                    icon: "\uf054"
                    color: ThemeManager.theme.labelSecondary
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    showComponent(repeatedComponent);
                }
            }
        }

        AlarmDialogProperty {
            id: musicStatus
            anchors.left: parent.left
            anchors.right: parent.right

            status: false
            text: "Music"
            image: "\uf001"

            trailing: QLabel {
                text: "Not supported yet"
                color: ThemeManager.theme.labelSecondary
            }
        }

        AlarmDialogProperty {
            id: lightStatus
            anchors.left: parent.left
            anchors.right: parent.right

            status: false
            text: "Light"
            image: "\uf0eb"

            trailing: QLabel {
                text: "Not supported yet"
                color: ThemeManager.theme.labelSecondary
            }
        }
    }
}
