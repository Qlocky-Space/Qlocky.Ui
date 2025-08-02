import QtQuick
import QtQuick.Layouts

import Ui

Item {
    id: root

    required property string title

    default property alias windowContent: valueItem.data

    implicitHeight: Math.max(100, itemLayout.implicitHeight)
    implicitWidth: itemLayout.implicitWidth

    Layout.fillWidth: true

    RowLayout {
        id: itemLayout
        anchors.fill: parent

        QLabel {
            text: root.title
            color: ThemeManager.theme.labelPrimary
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
        }

        Item { Layout.fillWidth: true } // Spacer

        RowLayout {
            id: valueItem
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        antialiasing: true
        height: 2

        color: ThemeManager.theme.miscellaneousSeperatorOpaque
    }
}