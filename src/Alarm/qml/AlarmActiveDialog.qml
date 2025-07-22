import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property var viewModel: AlarmActiveDialogViewModel
    property var alarm: viewModel.item

    property string alarmId

    implicitWidth: 1300
    implicitHeight: 520

    acceptShow: false
    cancelShow: false

    onOpened: {
        viewModel.loadAlarm(alarmId);
    }

    Item {
        id: content
        anchors.fill: parent
        anchors.margins: 16

        QLabel {
            id: title
            text: alarm.displayName
            font.bold: true
            font.pixelSize: 72
            color: ThemeManager.theme.labelPrimary

            anchors.horizontalCenter: parent.horizontalCenter
        }

        QLabel {
            id: description
            text: qsTr("Alarm Description")
            color: ThemeManager.theme.labelPrimary

            anchors.right: parent.right
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter

            wrapMode: Text.WordWrap
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            QConfirmationSlider {
                id: dismissButton

                confirmText: qsTr("Slide to dismiss")
                color: ThemeManager.theme.red

                onConfirmed: {
                    viewModel.dismiss();
                    root.close();
                }
            }

            QButton {
                id: snoozeButton
                text: qsTr("Snooze")

                buttonStyle: QButton.ButtonStyle.Filled
                backgroundColor: ThemeManager.theme.blue

                image: "\uf0f3"
                onClicked: {
                    viewModel.snooze();
                    root.close();
                }
            }
        }
    }
}
