import QtQuick
import QtQuick.Controls
import QtQuick.Effects

import Ui

Item {
    id: root

    anchors.fill: parent

    signal opened()
    signal closed()

    function open() {
        dialog.open()
    }

    function close() {
        dialog.close()
    }

    default property alias windowContent: windowContentItem.data

    Item {
        id: windowContentItem
        anchors.fill: parent
    }
}