import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import AppShell 1.0

AppWindow {
    id: root

    Item {
        id: contentArea

        anchors.top: appStatusBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        WindowContent {
            id: window

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    StatusBar {
        id: appStatusBar

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 50
    }
}
