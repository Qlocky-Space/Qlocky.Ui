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
            var params = data.value("params")
            var path = data.value("path")
            console.log("open page - path: " + path + ", params: " + JSON.stringify(params))

            pageLoader.setSource(path, params)

            provider.cleanup(data)
        }

        function onFireOpenDialog(data) {
            var params = data.value("params")
            var path = data.value("path")
            console.log("open dialog - path: " + path + ", params: " + JSON.stringify(params))

            dialogLoader.setSource(path, params)
            dialogLoader.open()

            provider.cleanup(data)
        }
    }
}