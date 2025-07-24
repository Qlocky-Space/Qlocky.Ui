import QtQuick
import QtQuick.Effects

import Ui

Item {
    id: root

    property real size: 80
    property string icon

    signal clicked()

    implicitWidth: size
    implicitHeight: size

    // White shadow background
    QButton {
        id: button
        anchors.centerIn: parent

        image: root.icon
        onClicked: root.clicked()
        buttonStyle: QButton.ButtonStyle.Plain
        imageSize: size - 32
    }

    MultiEffect {
        source: button
        anchors.fill: button
        shadowBlur: 1.0
        shadowEnabled: true
        shadowColor: ThemeManager.theme.labelPrimary
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
    }
}