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
    implicitHeight: content.implicitHeight

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
            text: qsTr("Snooze")

            implicitHeight: 100
            implicitWidth: 300

            buttonStyle: QButton.ButtonStyle.Filled
            backgroundColor: ThemeManager.theme.blue

            image: "\uf04b"
            imageSize: 64
            onClicked: {
                viewModel.snooze();
                root.close();
            }
        }

        QButton {
            id: dismissButton
            text: qsTr("Dismiss")

            implicitHeight: 100
            implicitWidth: 300

            buttonStyle: QButton.ButtonStyle.Filled
            backgroundColor: ThemeManager.theme.red

            image: "\uf1f6"
            imageSize: 64
            onClicked: {
                viewModel.dismiss();
                root.close();
            }
        }
    }
}
