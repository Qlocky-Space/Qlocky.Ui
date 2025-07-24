import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import AppShell 1.0
import Ui
import Widget

Item {
    property var viewModel: MainPageViewModel

    // Background wallpaper
    Image {
        id: bgImage
        anchors.fill: parent
        opacity: 0.8
        source:  ThemeManager.currentTheme == ThemeManager.ThemeMode.Light ? "/AppShell/resources/wallpaper-light.jpg" : "/AppShell/resources/wallpaper-dark.png"
        fillMode: Image.PreserveAspectCrop
    }

    // Main content area
    Item {
        id: contentArea

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        WidgetLayout {
            id: window

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            // Columns
            columns: 5
            columnSpacing: 30
            // Row
            rows: 3
            rowSpacing: 30
            // Anchors
            anchors.fill: parent
            anchors.margins: 20

            Repeater {
                model: viewModel.widgets

                Loader {
                    source: model.source
                    Layout.row: model.row
                    Layout.rowSpan: model.rowSpan
                    Layout.column: model.column
                    Layout.columnSpan: model.columnSpan
                }
            }
        }
    }

    // Status bar at the top
    StatusBar {
        id: appStatusBar
    }
}
