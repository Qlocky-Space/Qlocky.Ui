import QtQuick
import QtQuick.Layouts

import Ui

Item {
    Column {
        anchors.centerIn: parent
        spacing: 16

        QIcon {
            anchors.horizontalCenter: parent.horizontalCenter
            icon: "\uf07c"
            size: 54
            color: ThemeManager.theme.labelPrimary
        }

        QLabel {
            text: qsTr("Your Library")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        QLabel {
            text: qsTr("Saved stations and sources will appear here.")
            color: ThemeManager.theme.labelSecondary
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}