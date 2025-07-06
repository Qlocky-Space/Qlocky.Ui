import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    Column {
        spacing: 10
        QButton {
            text: "Close Dialog"
            onClicked: {
                customDialog.close()
            }
        }
    }
}