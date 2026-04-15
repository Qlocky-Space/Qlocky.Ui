import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.VirtualKeyboard

import Ui

QDialog {
    property var viewModel: WiFiProfileDialogViewModel

    property string ssid

    implicitHeight: content.implicitHeight
    implicitWidth: 800

    onOpened: {
        viewModel.ssid = ssid;
        viewModel.password = "";
    }

    onCanceled: {
        close();
    }

    onAccepted: {
        viewModel.connectTo();
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
            text: viewModel.ssid
        }

        QTextField {
            hint: qsTr("Password")
            focus: true

            currentText: viewModel.password
            onTextEditingFinished: function(text) {
                viewModel.password = text;
            }

            clearTextButtonVisible: true
            inputField.passwordMaskDelay: 500
            inputField.echoMode: TextInput.Password
            inputField.inputMethodHints: Qt.ImhHiddenText
        }
    }
}