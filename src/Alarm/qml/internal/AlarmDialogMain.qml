import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    required property var alarm

    implicitHeight: content.implicitHeight
    implicitWidth: content.implicitWidth

    signal showComponent(Component component)
    signal done

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

            onClicked: function (time) {
                alarm.dueTime = TimeConverter.relativeTimeToUtc(time);
            }
        }

        AlarmDialogProperty {
            id: activeStatus

            anchors.left: parent.left
            anchors.right: parent.right

            status: alarm.state
            text: "Active"
            image: "\uf00c"

            button.onClicked: {
                alarm.state = !alarm.state;
            }

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

            status: alarm.daysOfWeek !== DayOfWeekViewModel.None
            text: "Repeat"
            image: "\uf363"

            button.onClicked: {
                if (alarm.daysOfWeek !== DayOfWeekViewModel.None) {
                    alarm.daysOfWeek = DayOfWeekViewModel.None;
                } else {
                    showComponent(repeatedComponent);
                }
            }

            onTrailingClicked: showComponent(repeatedComponent)

            trailing: AlarmDialogNavigateTrailing {
                text: AlarmDayUtils.getDaysDisplay(alarm.daysOfWeek)
            }
        }

        AlarmDialogProperty {
            id: musicStatus
            anchors.left: parent.left
            anchors.right: parent.right

            status: alarm.musicSourceId.length > 0
            text: "Music"
            image: "\uf001"

            onTrailingClicked: showComponent(musicComponent)

            button.onClicked: {
                if (alarm.musicSourceId.length > 0) {
                    alarm.musicSourceId = "";
                    alarm.musicSourceName = "";
                } else {
                    showComponent(musicComponent);
                }
            }

            trailing: AlarmDialogNavigateTrailing {
                text: alarm.musicSourceId.length > 0 ? alarm.musicSourceName : qsTr("Choose source")
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
