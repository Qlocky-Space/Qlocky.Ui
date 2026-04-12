import QtQuick
import QtQuick.Layouts

import Ui

Item {
    Column {
        anchors.centerIn: parent
        spacing: 16

        QIcon {
            anchors.horizontalCenter: parent.horizontalCenter
            icon: "\uf004"
            size: 54
            color: ThemeManager.theme.labelPrimary
        }

        QLabel {
            text: qsTr("Favorites")
            anchors.horizontalCenter: parent.horizontalCenter
        }

        QLabel {
            text: qsTr("Your favorite radio sources will appear here.")
            color: ThemeManager.theme.labelSecondary
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
