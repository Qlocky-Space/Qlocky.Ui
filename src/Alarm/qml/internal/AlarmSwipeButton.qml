import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    id: root

    required property string icon
    required property color color

    signal clicked

    width: 150
    height: parent.height

    Rectangle {
        anchors.fill: parent
        color: root.color
    }

    QIcon {
        anchors.centerIn: parent
        size: 48
        icon: root.icon
    }

    SwipeDelegate.onClicked: {
        clicked()
    }
}