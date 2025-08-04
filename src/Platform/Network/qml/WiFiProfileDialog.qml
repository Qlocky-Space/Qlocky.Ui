import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.VirtualKeyboard

import Ui

QDialog {
    property string ssid
    property string securityType: "WPA-PSK"


    implicitHeight: content.implicitHeight
    implicitWidth: 800

    onCanceled: {
        close();
    }

    onAccepted: {
        // viewModel.save();
        close();
    }

    Column {
        id: content
        anchors.fill: parent
        spacing: 15

        QLabel {
            text: qsTr("Wi-Fi Profile")
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        QLabel {
            text: ssid
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}