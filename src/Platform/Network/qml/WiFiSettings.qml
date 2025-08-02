import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root
    anchors.fill: parent

    QLabel {
        text: qsTr("Wifi Settings")
        font: FontStyle.h2
        horizontalAlignment: Text.AlignHCenter
    }
}
