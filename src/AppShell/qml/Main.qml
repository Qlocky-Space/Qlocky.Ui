import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import AppShell 1.0
import Ui

AppWindow {
    id: root

    Loader {
        id: pageProvider
        anchors.fill: parent
    }

    QDialogProvider {
        id: dialogProvider
        backgroundSourceItem: pageProvider
    }

    QInteractiveProvider {
        pageLoader: pageProvider
        dialogLoader: dialogProvider
    }
}
