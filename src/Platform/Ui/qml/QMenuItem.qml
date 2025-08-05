import QtQuick
import QtQuick.Controls as T
import QtQuick.Layouts

import Ui

T.MenuItem {
    id: menuItem

    implicitWidth: 400
    implicitHeight: 100

    arrow: QIcon {
        implicitWidth: 40
        implicitHeight: 100

        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 16

        visible: menuItem.subMenu
        color: ThemeManager.theme.blue
        icon: "\uf054"
    }

    contentItem: QLabel {
        text: menuItem.text
        Layout.fillWidth: true
    }

    background: Rectangle {
        color: menuItem.highlighted ? ThemeManager.theme.fillsPrimary : "transparent"
        radius: 8
    }
}