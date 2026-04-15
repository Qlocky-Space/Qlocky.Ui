pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts

import Ui

Rectangle {
    id: root

    property var items: []
    property int currentIndex: 0

    signal itemSelected(int index, var item)

    radius: 28
    color: Qt.darker(ThemeManager.theme.fillsSecondary, 1.08)

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 24
        anchors.rightMargin: 24
        spacing: 10

        Repeater {
            model: root.items

            delegate: Item {
                id: delegateRoot

                required property var modelData
                required property int index

                Layout.fillWidth: true
                Layout.fillHeight: true

                readonly property bool selected: root.currentIndex === index
                readonly property color itemColor: selected ? ThemeManager.theme.labelPrimary : ThemeManager.theme.labelSecondary

                Column {
                    anchors.centerIn: parent
                    spacing: 8

                    QIcon {
                        anchors.horizontalCenter: parent.horizontalCenter
                        icon: delegateRoot.modelData.icon
                        size: 35
                        color: delegateRoot.itemColor
                    }

                    QLabel {
                        text: delegateRoot.modelData.text
                        color: delegateRoot.itemColor
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor

                    onClicked: {
                        root.currentIndex = delegateRoot.index;
                        root.itemSelected(delegateRoot.index, delegateRoot.modelData);
                    }
                }
            }
        }
    }
}
