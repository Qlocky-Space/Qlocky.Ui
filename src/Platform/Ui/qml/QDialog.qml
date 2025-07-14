import QtQuick
import QtQuick.Controls
import QtQuick.Effects

import Ui

Item {
    id: root

    anchors.fill: parent
    anchors.margins: 20

    signal opened
    signal closed
    signal canceled
    signal accepted

    function open() {
        dialog.open();
    }

    function close() {
        dialog.close();
    }

    default property alias windowContent: windowContentItem.data

    property alias cancelText: cancelButton.text
    property alias acceptText: acceptButton.text

    Item {
        id: headerItem
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 100

        QButton {
            id: cancelButton
            anchors.left: parent.left
            anchors.top: parent.top
            buttonStyle: QButton.ButtonStyle.Plain

            text: qsTr("Cancel")
            onClicked: root.canceled()
        }

        QButton {
            id: acceptButton
            anchors.right: parent.right
            anchors.top: parent.top
            buttonStyle: QButton.ButtonStyle.Tinted

            text: qsTr("Accept")
            onClicked: root.accepted()
        }
    }

    Item {
        id: windowContentItem

        anchors.top: headerItem.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
