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

    Item {
        id: content
        anchors.fill: parent

        QButton {
            id: snoozeButton
            text: qsTr("Snooze")

            implicitHeight: 100
            implicitWidth: 250

            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: dismissButton.left
            anchors.rightMargin: 16

            buttonStyle: QButton.ButtonStyle.Filled
            backgroundColor: ThemeManager.theme.blue

            image: "\uf04b"
            imageSize: 64
            onClicked: {
                viewModel.snooze();
                root.close();
            }
        }

        QConfirmationSlider {
            confirmText: qsTr("Slide to dismiss")
            color: ThemeManager.theme.red

            anchors.right: parent.right
            anchors.rightMargin: 16
            anchors.left: snoozeButton.right
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter

            onConfirmed: {
                viewModel.dismiss();
                root.close();
            }
        }
    }
}
