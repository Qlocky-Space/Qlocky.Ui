import QtQuick
import QtQuick.Layouts

import Ui

Item {
    id: root
    property bool active: false

    implicitHeight: 132

    Rectangle {
        id: background
        anchors.fill: parent

        color: root.active ? ThemeManager.theme.fillsPrimary : ThemeManager.theme.fillsQuaternary
    }

    RowLayout {
        anchors.fill: parent
        spacing: 20

        anchors.horizontalCenter: parent.horizontalCenter

        QLabel {
            text: "6:20"
        }

        QLabel {
            text: "Imgs"
        }

        QToggleButton {
            checked: root.active

            onToggled: function(state) {
                root.active = state
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.active = !root.active
        }
    }
}