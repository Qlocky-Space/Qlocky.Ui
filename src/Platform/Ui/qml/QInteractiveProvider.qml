import QtQuick
import QtQuick.Controls
import QtQuick.Effects

import Ui

Item {
    id: root

    property var provider: InteractiveProvider
    property var pageLoader
    property var dialogLoader

    Connections {
        target: root.provider

        function onFireOpenPage(data) {
            pageLoader.source = data.value("path")
        }

        function onFireOpenDialog(data) {
            dialogLoader.source = data.value("path")
            dialogLoader.open()
        }
    }
}