import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root

    required property string hostname
    property string editHostname: hostname

    implicitHeight: content.implicitHeight
    implicitWidth: content.implicitWidth

    signal changeHostname(string newHostname)

    function save() {
        if (editHostname !== hostname) {
            changeHostname(editHostname);
            root.state = "SHOW";
        }
    }

    states: [
        State {
            name: "SHOW"
        },
        State {
            name: "EDIT"
        }
    ]
    state: "SHOW"

    ColumnLayout {
        id: content
        anchors.centerIn: parent
        anchors.margins: 16
        spacing: 28

        Image {
            source: "/Device/resources/DeviceFrame.png"
            width: 80
            fillMode: Image.PreserveAspectFit
            Layout.alignment: Qt.AlignHCenter
        }

        QLabel {
            visible: root.state === "SHOW"
            text: root.hostname
            Layout.alignment: Qt.AlignHCenter
        }

        QTextField {
            id: hostnameInput

            visible: root.state === "EDIT"
            hint: qsTr("Enter new hostname")

            currentText: root.editHostname
            textHorizontalAlignment: TextInput.AlignHCenter
            onTextEditingFinished: function(text) {
                root.editHostname = text
            }

            onAccepted: {
                root.save();
            }
            onEscaped: {
                root.state = "SHOW";
            }

            Layout.alignment: Qt.AlignHCenter
            width: 200
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            spacing: 16

            QButton {
                visible: root.state === "EDIT"
                text: qsTr("Cancel")
                buttonStyle: QButton.ButtonStyle.Tinted
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    root.state = "SHOW"
                }
            }

            QButton {
                text: root.state === "SHOW" ? qsTr("Change Hostname") : qsTr("Save")
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    if (root.state === "SHOW") {
                        root.editHostname = root.hostname
                        root.state = "EDIT"
                        hostnameInput.forceActiveFocus()
                    } else {
                        root.save()
                    }
                }
            }
        }
    }

}