import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui

ApplicationWindow {
    id: root
    objectName: "ApplicationWindow"

    visible: true

    color: ThemeManager.theme.backgroundPrimary

    width: 1920
    height: 1080

    default property alias windowContent: windowContentItem.data

    Component.onCompleted: {
        MainWindowViewModel.window = root
    }

    Item {
        id: windowContentItem
        anchors.fill: parent
    }
}
