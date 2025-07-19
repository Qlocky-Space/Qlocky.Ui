import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui
import Alarm

Item {
    id: root

    property var viewModel: AlarmListCardViewModel

    ListView {
        id: listView
        snapMode: ListView.SnapOneItem
        anchors.fill: parent
        clip: true

        model: viewModel.alarms

        delegate: AlarmListItem {
            required property var alarm

            alarmId: alarm.alarmId
            displayName: alarm.displayName
            isEnabled: alarm.state
            dueTime: Qt.formatDateTime(new Date(alarm.dueTime * 1000), "HH:mm")

            width: listView.width

            onActivationToggled: function (isEnabled) {
                if (isEnabled) {
                    viewModel.activateAlarm(alarmId);
                } else {
                    viewModel.deactivateAlarm(alarmId);
                }
            }
        }
    }
}
