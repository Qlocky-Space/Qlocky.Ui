import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui

Item {
    id: titlebar

    anchors.fill: parent

    property var viewModel: StatusBarViewModel

    property color fontColor: ThemeManager.theme.labelPrimary

    // Status bar content
    QStatusBarContent {
        id: statusBarContent
        viewModel: titlebar.viewModel

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    // Custom swipe gesture where pointer must be draged at least 200pixel
    // to open the overlay
    MouseArea {
        id: swipeArea
        anchors.fill: statusBarContent
        drag.target: statusBarContent
        drag.axis: Drag.YAxis
        drag.threshold: 20

        property real startY: 0
        property real distanceY: 0
        property real maxDistance: 200
        property real threshold: 0.97

        onPressed: function(mouse) {
            startY = mouse.y;
        }

        onPositionChanged: {
            var raw = (swipeArea.mouseY - startY) / maxDistance;
            distanceY = Math.max(0, Math.min(threshold, raw));

            overlayBackground.opacity = distanceY
        }

        onReleased:  function(mouse) {
            if (distanceY < threshold) {
                overlay.close()
                overlayBackground.opacity = 0
            }
            else {
                overlay.open()
            }
        }
    }

    // The overlay background
    Item {
        id: overlayBackground
        opacity: 0
        anchors.fill: parent

        Image {
            anchors.fill: parent
            source:  ThemeManager.currentTheme == ThemeManager.ThemeMode.Light ? "/AppShell/resources/wallpaper-light.jpg" : "/AppShell/resources/wallpaper-dark.png"
            fillMode: Image.PreserveAspectCrop
        }

        Rectangle {
            anchors.fill: parent
            color: ThemeManager.theme.black
            opacity: Math.max(0, overlayBackground.opacity - 0.8)
        }

        QHomeIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30
        }

        QStatusBarContent {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right

            viewModel: titlebar.viewModel
        }

        Behavior on opacity {
            NumberAnimation { duration: 400; easing.type: Easing.OutQuad }
        }
    }

    // The overlay content
    Popup {
        id: overlay
        x: parent.width / 2 - width / 2
        y: 100
        focus: true
        modal: false
        dim: false
        closePolicy: Qt.inputMethod.visible ? Popup.CloseOnEscape : Popup.CloseOnEscape | Popup.CloseOnPressOutside

        // Min height/width
        height: Math.max(contentItem.implicitHeight, 500)
        width: Math.max(contentItem.implicitWidth, 700)

        background: null

        contentItem: QStatusBarOverlay {
            anchors.fill: parent
            viewModel: titlebar.viewModel
        }

        onVisibleChanged: {
            if (!visible) {
                overlayBackground.opacity = 0
            }
        }
    }
}
