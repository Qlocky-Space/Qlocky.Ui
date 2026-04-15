import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    id: root

    required property string title
    property color titleColor: ThemeManager.theme.labelPrimary

    property Component additionalContent: null
    property alias menu: menuContext

    default property alias windowContent: valueItem.data

    property bool clickable: false
    signal clicked()

    implicitHeight: Math.max(100, itemLayout.implicitHeight)
    implicitWidth: itemLayout.implicitWidth

    Layout.fillWidth: true

    RowLayout {
        id: itemLayout
        anchors.fill: parent

        QLabel {
            text: root.title
            color: root.titleColor
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillHeight: true
        }

        Item { Layout.fillWidth: true } // Spacer

        RowLayout {
            id: valueItem
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.fillHeight: true

            Loader {
                sourceComponent: root.additionalContent
                visible: root.additionalContent !== null
            }
        }
    }

    Rectangle {
        id: indicator

        property int mx
        property int my
        x: mx - width / 2
        y: my - height / 2
        radius: height / 2
        color: ThemeManager.theme.miscellaneousSeperatorNonOpaque
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        enabled: root.clickable

        onClicked: {
            indicator.mx = mouseArea.mouseX;
            indicator.my = mouseArea.mouseY;

            main.restart();
            root.clicked();
        }

        onPressAndHold: {
            indicator.mx = mouseArea.mouseX;
            indicator.my = mouseArea.mouseY;
            menuContext.open()
        }
    }

    QMenu {
        id: menuContext
        x: indicator.mx
        y: indicator.my
    }

    ParallelAnimation {
        id: main
        NumberAnimation {
            target: indicator
            properties: "width"
            from: 0
            to: root.width
            duration: 200
        }
        NumberAnimation {
            target: indicator
            properties: "height"
            from: 0
            to: root.height
            duration: 200
        }
        NumberAnimation {
            target: indicator
            properties: "opacity"
            from: 0.6
            to: 0
            duration: 200
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