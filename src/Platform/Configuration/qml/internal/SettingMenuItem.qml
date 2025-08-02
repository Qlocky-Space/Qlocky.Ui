import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Control {
    id: root

    required property string title
    required property int index

    signal clicked()

    width: 680

    padding: 50

    QLabel {
        text: title
        font: FontStyle.body

        color: ThemeManager.theme.labelPrimary
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 32
    }

    QIcon {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        color: ThemeManager.theme.blue
        icon: "\uf054"
    }

    MouseArea {
        anchors.fill: parent

        onClicked: root.clicked()
    }
}