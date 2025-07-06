import QtQuick
import QtQuick.Controls
import QtQuick.Effects

import Ui

Item {
    id: root

    anchors.fill: parent

    property Item backgroundSourceItem
    property string source: ""

    function open() {
        customDialog.open()
    }

    function close() {
        customDialog.close()
    }

    Component.onCompleted: {
        // Becasue blur effect takes some time to render,
        // live update is enabled so no delay is visible when
        // dialog opens. To ensure live update is started, opacity
        // must be 1 and when component is loaded, it will be transparent
        blurEffect.opacity = 0
        shaderSource.opacity = 0
    }

    ShaderEffectSource {
        id: shaderSource
        anchors.fill: parent
        sourceItem: backgroundSourceItem
        live: true
        visible: true
        opacity: 1
    }

    ShaderEffect {
        id: blurEffect

        property var src: shaderSource
        property int radius: 12
        property real deviation: 24
        property var pixelStep: Qt.vector2d(1/src.width, 1/src.height)

        fragmentShader: "/Ui/resources/shaders/gaussianblur.frag.qsb"
        anchors.fill: parent

        opacity: 1
        visible: true
        z: 1

        Behavior on opacity {
            NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
        }
    }

    Popup {
        id: customDialog
        anchors.centerIn: parent
        focus: true
        modal: true
        dim: false
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        // Min height/width
        height: Math.max(contentItem.implicitHeight + 40, 500)
        width: Math.max(contentItem.implicitWidth + 40, 700)

        background: Rectangle {
            color: ThemeManager.theme.backgroundSecondary
            radius: 30
        }

        contentItem: Loader {
            source: root.source
        }

        onVisibleChanged: {
            if (visible) {
                blurEffect.opacity = 1
            } else {
                blurEffect.opacity = 0
            }
        }
    }
}