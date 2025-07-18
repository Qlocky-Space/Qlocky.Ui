import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property var viewModel: AlarmDialogViewModel
    property var alarm: viewModel.item

    property string alarmId

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

        QToggleButton {
            checked: alarm.state

            onToggled: function (state) {
                alarm.state = state;
            }
        }

        QLabel {
            text: "Active " + (alarm.state ? "Yes" : "No")
        }

        QLabel {
            text: "Music"
        }

        QLabel {
            text: "Light"
        }
    }
}
