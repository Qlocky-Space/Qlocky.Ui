import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property var viewModel: AlarmDialogViewModel
    property var alarm: viewModel.item

    property string alarmId

    implicitWidth: 800
    implicitHeight: content.implicitHeight + 180

    onOpened: {
        viewModel.loadAlarm(alarmId);
    }

    onCanceled: {
        close();
    }

    onAccepted: {
        viewModel.save();
        close();
    }

    ColumnLayout {
        id: content
        anchors.fill: parent
        spacing: 15

        QTimePicker {
            id: timePicker
            date: alarm.dueTime
            width: root.implicitWidth

            Layout.topMargin: 10
            Layout.bottomMargin: 10

            onClicked: function(date) {
                alarm.dueTime = date
            }
        }

        AlarmDialogProperty {
            id: activeStatus
            Layout.fillWidth: true

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
            id: snoozeStatus
            Layout.fillWidth: true

            status: false
            text: "Snooze"
            image: "\u003f"

            trailing: QLabel {
                text: "Not supported yet"
            }
        }

        AlarmDialogProperty {
            id: musicStatus
            Layout.fillWidth: true

            status: false
            text: "Music"
            image: "\uf001"

            trailing: QLabel {
                text: "Not supported yet"
            }
        }

        AlarmDialogProperty {
            id: lightStatus
            Layout.fillWidth: true

            status: false
            text: "Light"
            image: "\uf0eb"

            trailing: QLabel {
                text: "Not supported yet"
            }
        }
    }
}
