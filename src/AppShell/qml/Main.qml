import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui

AppWindow {
    id: root

    Loader {
        id: pageProvider
        anchors.fill: parent
    }

    QDialogProvider {
        id: dialogProvider
    }

    QInteractiveProvider {
        pageLoader: pageProvider
        dialogLoader: dialogProvider
    }
}
