import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui

AppWindow {
    id: root

    Flickable {
        id: flickable
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        height: Qt.inputMethod.visible ?  parent.height - keyboard.input.y : parent.height

        contentWidth: parent.width
        contentHeight: parent.height
        interactive: false

        Loader {
            id: pageProvider
            anchors.fill: parent
        }

        QDialogProvider {
            id: dialogProvider
        }

        QInteractiveProvider {
            pageLoader: pageProvider
            dialogLoader: dialogProvider
        }

        // Ensures the flickable is scrolled to selected element
        // when the keyboard is visible
        AutoScroller {
            outerFlickable: flickable
        }
    }

    // Ensure the input panel is always above other content, also
    // popup is shown below
    Overlay.overlay.children: [
        QKeyboard {
            id: keyboard
        }
    ]
}
