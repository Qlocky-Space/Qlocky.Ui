import QtQuick
import QtQuick.Controls

import Ui

Item {
    id: root

    property color color: ThemeManager.theme.blue
    property color foreground: ThemeManager.theme.labelPrimary

    property string image

    property real value: 0.0

    implicitWidth: 500
    implicitHeight: 90

    signal valueUpdated(real newValue)

    Rectangle {
        id: sliderBackground
        anchors.fill: parent
        radius: 20
        color: ThemeManager.theme.backgroundTertiary

        clip: true

        QRoundedRectangle {
            readonly property real threshold: 10

            id: sliderTrack
            width: 0
            anchors.left: parent.left
            height: parent.height
            color: root.color
            // Adjust corner radius based on the slider's width, because parent has radius and clip only works with rectangle
            cornerSide: ((parent.width - sliderTrack.width) <= threshold) || ((parent.width - sliderTrack.width) >= parent.width - threshold * 3.0)
                ? QRoundedRectangle.Direction.All
                : QRoundedRectangle.Direction.Left
        }

        QIcon {
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter

            color: root.foreground
            icon: root.image
            size: 32
        }
    }

    MouseArea {
        id: dragArea
        anchors.fill: sliderBackground
        drag.target: sliderTrack
        drag.axis: Drag.XAxis
        drag.minimumX: 0
        drag.maximumX: sliderBackground.width


        onPressed: {
            sliderTrack.width = dragArea.mouseX;

            var value = Math.max(0, Math.min(1, sliderTrack.width / sliderBackground.width));
            root.valueUpdated(value * 100);
        }

        onPositionChanged: {
            sliderTrack.width = Math.min(Math.max(0, dragArea.mouseX), sliderBackground.width);

            var value = Math.max(0, Math.min(1, sliderTrack.width / sliderBackground.width));
            root.valueUpdated(value * 100);
        }
    }


    onValueChanged: {
        if (dragArea.pressed) {
            return;
        }
        var value = Math.max(0, Math.min(1, root.value / 100));
        sliderTrack.width = value * sliderBackground.width;
    }
}
