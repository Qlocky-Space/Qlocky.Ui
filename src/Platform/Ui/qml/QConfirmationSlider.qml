
import QtQuick 2.15
import QtQuick.Controls 2.15

import Ui

Item {
    id: root

    property alias sliderWidth: sliderBackground.width
    property alias sliderHeight: sliderBackground.height

    property color color: ThemeManager.theme.blue
    property color foreground: ThemeManager.theme.white

    signal confirmed()

    width: 500
    height: 90

    property string confirmText: qsTr("Slide to confirm")
    property string confirmedText: qsTr("Confirmed")

    Rectangle {
        id: sliderBackground
        anchors.fill: parent
        radius: height / 2
        color: ThemeManager.theme.backgroundTertiary
    }

    QRoundedRectangle {
        id: sliderTrack
        x: 15
        y: (parent.height - height) / 2
        width: handle.x + handle.width / 2
        height: parent.height
        radius: height / 2
        color: root.color
        cornerSide: {
            if (dragArea.drag.active && dragArea.dragX > 20) {
                return QRoundedRectangle.Direction.Left;
            }
            if (root.isConfirmed) {
                return QRoundedRectangle.Direction.Left;
            }

            return QRoundedRectangle.Direction.All;
        }
        z: 1
    }

    property bool isConfirmed: false

    QLabel {
        id: label
        anchors.centerIn: parent
        text: isConfirmed ? root.confirmedText : root.confirmText
        color: root.foreground
        opacity: !isConfirmed ? 0.5 : 1
        z: 3
    }

    Rectangle {
        id: handle
        width: parent.height
        height: parent.height
        radius: width / 2
        color: root.foreground
        x: {
            if (root.isConfirmed) {
                return root.width - width
            }
            if (dragArea.drag.active) {
                return dragArea.dragX
            }
            if (handleAnim.running) {
                return handleAnim.to
            }
            return 0
        }
        y: 0
        z: 4

        QIcon {
            anchors.centerIn: parent
            color: root.color
            icon: "\uf054"
            size: 32
        }

        property real dragX: 0

        Behavior on x {
            NumberAnimation { duration: 200; easing.type: Easing.OutQuad }
        }

        MouseArea {
            id: dragArea
            enabled: !root.isConfirmed
            anchors.fill: parent
            drag.target: handle
            drag.axis: Drag.XAxis
            drag.minimumX: 0
            drag.maximumX: root.width - handle.width
            property real dragX: handle.x

            onReleased: {
                if (handle.x >= root.width - handle.width - 2) {
                    root.isConfirmed = true
                    root.confirmed()
                } else {
                    handleAnim.to = 0
                    handleAnim.start()
                }
            }
        }
    }

    NumberAnimation {
        id: handleAnim
        target: handle
        property: "x"
        to: 0
        duration: 200
    }
}
