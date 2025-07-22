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

    property bool acceptShow: true
    property bool cancelShow: true

    Item {
        id: headerItem
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: visible ? 100 : 0

        visible: acceptShow || cancelShow

        QButton {
            id: cancelButton
            anchors.left: parent.left
            anchors.top: parent.top
            buttonStyle: QButton.ButtonStyle.Plain

            visible: cancelShow

            text: qsTr("Cancel")
            onClicked: root.canceled()
        }

        QButton {
            id: acceptButton
            anchors.right: parent.right
            anchors.top: parent.top
            buttonStyle: QButton.ButtonStyle.Tinted

            visible: acceptShow

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
