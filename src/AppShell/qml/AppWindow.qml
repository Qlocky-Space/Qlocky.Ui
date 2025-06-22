import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import AppShell 1.0

ApplicationWindow {
    id: root
    objectName: "ApplicationWindow"

    visible: true

    color: "#16171A"

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
