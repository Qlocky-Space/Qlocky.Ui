import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import AppShell 1.0
import Ui

AppWindow {
    id: root

    Loader {
        id: mainLoader
        anchors.fill: parent
        source: MainWindowViewModel.pageUrl
    }

}
