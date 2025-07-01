import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import AppShell 1.0
import Ui

AppWindow {
    id: root

    // Background wallpaper
    Image {
        id: bgImage
        anchors.fill: parent
        opacity: 0.5
        source: ThemeManager.currentTheme == ThemeManager.ThemeMode.Light ? "/AppShell/resources/wallpaper-light.jpg" : "/AppShell/resources/wallpaper-dark.png"
        fillMode: Image.PreserveAspectCrop
    }
    MultiEffect {
        source: bgImage
        anchors.fill: bgImage
        blurEnabled: true
        blurMax: 12
        blur: 50.0
    }

    // Main content area
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

    // Status bar at the top
    StatusBar {
        id: appStatusBar

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        height: 80
    }
}
