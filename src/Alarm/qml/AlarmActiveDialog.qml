import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property var viewModel: AlarmActiveDialogViewModel
    property var alarm: viewModel.item

    property string alarmId

    implicitWidth: 800
    implicitHeight: content.implicitHeight + 180

    acceptShow: false
    cancelShow: false

    onOpened: {
        viewModel.loadAlarm(alarmId);
    }

    ColumnLayout {
        id: content
        anchors.fill: parent
        spacing: 15

        QLabel {
            text: "Alarm Id" + alarm.alarmId
            font.pixelSize: 24
            Layout.topMargin: 10
            Layout.bottomMargin: 10
        }

        QButton {
            id: snoozeButton

            height: 150
            width: 450
            buttonStyle: QButton.ButtonStyle.Filled

            text: qsTr("Snooze")
            onClicked: {
                viewModel.snooze();
                root.close();
            }
        }

        QButton {
            id: dismissButton

            height: 75
            width: 300
            buttonStyle: QButton.ButtonStyle.Tinted

            text: qsTr("Dismiss")
            onClicked: {
                viewModel.dismiss();
                root.close();
            }
        }
    }
}
