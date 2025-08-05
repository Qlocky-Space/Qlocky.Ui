import QtQuick
import QtQuick.Controls
import QtQuick.Effects

import Ui

Item {
    id: root

    anchors.fill: parent


    function open() {
        blurEffect.opacity = 0.8
        delayDialogTimer.start()
    }

    function close() {
        dialog.close()
    }

    function setSource(uri, params) {
        contentLoader.setSource(uri, params)
    }

    Component.onCompleted: {
        // Becasue blur effect takes some time to render,
        // live update is enabled so no delay is visible when
        // dialog opens. To ensure live update is started, opacity
        // must be 1 and when component is loaded, it will be transparent
        blurEffect.opacity = 0
        // shaderSource.opacity = 0
    }

    Timer {
        id: delayDialogTimer
        repeat: false
        interval: 300

        onTriggered: {
            dialog.open()
        }
    }

    // TODO for performance reasons, this is replaced with a simple Rectangle
    //       with a solid color. If you want to use blur effect, uncomment
    //       the code below and comment out the Rectangle.
    //
    // ShaderEffectSource {
    //     id: shaderSource
    //     anchors.fill: parent
    //     sourceItem: backgroundSourceItem
    //     live: true
    //     visible: true
    //     opacity: 1
    // }

    // ShaderEffect {
    //     id: blurEffect

    //     property var src: shaderSource
    //     property int radius: 12
    //     property real deviation: 24
    //     property var pixelStep: Qt.vector2d(1/src.width, 1/src.height)

    //     fragmentShader: "/Ui/resources/shaders/gaussianblur.frag.qsb"
    //     anchors.fill: parent

    //     opacity: 1
    //     visible: true
    //     z: 1

    //     Behavior on opacity {
    //         NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
    //     }
    // }

    Rectangle {
        id: blurEffect
        anchors.fill: parent

        color: ThemeManager.theme.black

        opacity: 0.8
        visible: true
        z: 1

        Behavior on opacity {
            NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
        }

        // Ensure when the virtual keyboard is visible, the dialog
        // is not closed when clicking outside of it.
        MouseArea {
            anchors.fill: parent
            // No onClicked handler needed; this just blocks events
            enabled: Qt.inputMethod.visible
        }
    }

    Popup {
        id: dialog
        anchors.centerIn: parent
        focus: true
        // Workaround, if set to true, virtual keyboard second function key
        // will not work properly, so it is set to false. Therefore a MouseArea
        // in blureEffect is used to block events when the virtual keyboard is visible.
        modal: !Qt.inputMethod.visible
        dim: false
        closePolicy: Qt.inputMethod.visible ? Popup.CloseOnEscape : Popup.CloseOnEscape | Popup.CloseOnPressOutside

        // Min height/width
        height: Math.max(contentItem.implicitHeight, 500)
        width: Math.max(contentItem.implicitWidth, 700)

        background: Rectangle {
            anchors.fill: parent

            color: ThemeManager.theme.backgroundSecondary
            radius: 30
        }

        contentItem: Loader {
            anchors.fill: parent

            id: contentLoader
        }

        onVisibleChanged: {
            if (visible) {
                blurEffect.opacity = 0.8
                if (contentLoader.status === Loader.Ready && contentLoader.item?.opened) {
                    contentLoader.item.opened()
                }
            } else {
                blurEffect.opacity = 0
                if (contentLoader.status === Loader.Ready && contentLoader.item?.closed) {
                    contentLoader.item.closed()
                }
            }
        }
    }
}