import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui
import Alarm

Item {
    id: root

    ListView  {
        id: listView
        snapMode: ListView.SnapOneItem
        anchors.fill: parent
        clip: true

        model: AlarmListCardViewModel.alarms

        delegate: AlarmListItem {
            required property var alarm

            alarmId: alarm.alarmId
            displayName: alarm.displayName
            isEnabled: alarm.state
            dueTime: Qt.formatDateTime(alarm.dueTime, "HH:mm") // TODO use 24HFormat from persistency

            width: listView.width

            onActivationToggled: function (isEnabled) {
                if (isEnabled) {
                    AlarmListCardViewModel.activateAlarm(alarmId)
                }
                else {
                    AlarmListCardViewModel.deactivateAlarm(alarmId)
                }
            }
        }
    }
}