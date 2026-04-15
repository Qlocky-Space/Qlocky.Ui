import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QWidget {
    id: widget

    anchors.fill: parent
    anchors.margins: 16

    Item {
        id: header
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        height: 128

        QRoundedRectangle {
            radius: widget.radius
            cornerSide: QRoundedRectangle.Direction.Up

            anchors.fill: parent
            color: ThemeManager.theme.backgroundTertiary
        }

        QLabel {
            id: title

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            text: qsTr("New Alarm")
        }

        QButton {
            image: "\u002b"
            imageSize: 32

            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 48

            height: 72
            width: 72

            onClicked: {
                CommandExecutor.dispatch("alarm-new");
            }
        }
    }

    AlarmList {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header.bottom
    }
}
