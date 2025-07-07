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

    QButton {
        text: root.text
        onClicked: {
            close()
        }
    }
}