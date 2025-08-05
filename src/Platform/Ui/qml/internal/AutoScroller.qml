import QtQuick
import QtQuick.VirtualKeyboard

Item {

    property var outerFlickable

    readonly property var inputItem: InputContext.priv.inputItem

    onInputItemChanged: {
        if (inputItem !== null) {
            delayedLoading.restart()
        }
    }

    function ensureVisible(flickable) {
        if (!Qt.inputMethod.visible) {
            // If no keyboard is visible, do nothing
            return;
        }

        var cursorRectangle = flickable.contentItem.mapFromItem(inputItem, inputItem.cursorRectangle.x, inputItem.cursorRectangle.y)

        // ensure inputItem is centered in the visible flickable
        var visibleFlickableHeight = flickable.contentHeight - flickable.height
        var targetY = cursorRectangle.y - (visibleFlickableHeight / 2)

        // truncate targetY to ensure it is within the bounds of the flickable content
        flickable.contentY = Math.min(Math.max(targetY, 0), flickable.contentHeight - visibleFlickableHeight)
    }

    Timer {
        id: delayedLoading
        interval: 10
        onTriggered: {
            ensureVisible(outerFlickable)
        }
    }

    Connections {
        ignoreUnknownSignals: true
        target: Qt.inputMethod

        function onVisibleChanged() {
            if (inputItem) {
                delayedLoading.restart()
            }
        }

        function onAnimatingChanged() {
            if (inputItem && !Qt.inputMethod.animating)  {
                delayedLoading.restart()
            }
        }

        function onKeyboardRectangleChanged() {
            if (inputItem)  {
                delayedLoading.restart()
            }
        }

        function onCursorRectangleChanged() {
            if (inputItem && inputItem.activeFocus) {
                delayedLoading.restart()
            }
        }
    }
}