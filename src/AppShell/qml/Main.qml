import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

import Ui

AppWindow {
    id: root

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

    // Ensure the input panel is always above other content, also
    // popup is shown below
    Overlay.overlay.children: [
        QKeyboard {
            id: keyboard
        }
    ]
}
