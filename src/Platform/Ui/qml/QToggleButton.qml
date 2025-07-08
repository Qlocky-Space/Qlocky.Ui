import QtQuick
import QtQuick.Effects

Item {
    id: root

    property bool checked: false

    signal toggled(bool checked)

    implicitHeight: 60
    implicitWidth: 110

    Rectangle {
        id: background
        anchors.fill: parent

        color: root.checked ? ThemeManager.theme.green : ThemeManager.theme.fillsSecondary
        radius: root.height / 2
    }

    MultiEffect {
        anchors.fill: knob
        source: knob
        shadowEnabled: true
        shadowColor: "#80000000"
        shadowBlur: 0.8
        shadowVerticalOffset: 2
    }

    Rectangle {
        id: knob
        width: root.height - 5
        height: width
        radius: width / 2
        color: ThemeManager.theme.white
        x: root.checked ? root.width - width - 2.5 : 2.5
        z: 1
        anchors.verticalCenter: parent.verticalCenter

        Behavior on x {
            NumberAnimation { duration: 150; easing.type: Easing.InOutQuad }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent

        enabled: root.enabled

        onClicked: {
            root.checked = !root.checked
            root.toggled(root.checked)
        }
    }
}