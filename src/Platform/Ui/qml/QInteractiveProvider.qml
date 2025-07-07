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
            pageLoader.setSource(data.value("path"), data.value("params"))
        }

        function onFireOpenDialog(data) {
            dialogLoader.setSource(data.value("path"), data.value("params"))
            dialogLoader.open()
        }
    }
}