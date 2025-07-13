import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    onOpened: {
        console.log("Opened")
    }

    onClosed: {
        console.log("Closed")
    }

    property string text: "Close Dialog"

    RowLayout {
        QButton {
            text: root.text
            onClicked: {
                close()
            }
        }

        QLabel {
            text: "Hallo Welt"
        }

        QToggleButton {

        }
    }
}