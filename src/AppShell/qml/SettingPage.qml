import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import AppShell 1.0
import Ui

Item {
    id: root
    anchors.fill: parent

    RowLayout {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        QButton {
            image: "\uf1b9"
            text: "Back"

            onClicked: {
                CommandExecutor.dispatch("nav-back")
            }
        }

        Text {
            text: "Settings"
            font.pixelSize: 24
            color: ThemeManager.currentTheme == ThemeManager.ThemeMode.Light ? "black" : "white"
            anchors.margins: 20
        }
    }
}
