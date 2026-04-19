import QtQuick
import QtQuick.Layouts

import Ui

QDialog {
    id: root

    implicitWidth: 720
    implicitHeight: 430

    acceptShow: false
    cancelShow: false

    function submit(state) {
        CommandExecutor.dispatch("lifecycleChangeRequest", {
            state: state
        });
        close();
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 30

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 56

            ColumnLayout {
                spacing: 14

                QButton {
                    Layout.alignment: Qt.AlignHCenter
                    implicitWidth: 160
                    implicitHeight: 160
                    radius: width / 2
                    buttonStyle: QButton.ButtonStyle.Filled
                    backgroundColor: ThemeManager.theme.blue
                    fontColor: ThemeManager.theme.white
                    image: "\uf2f1"
                    imageSize: 62
                    onClicked: root.submit("Restart")
                }

                QLabel {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Restart")
                    color: ThemeManager.theme.labelPrimary
                }
            }

            ColumnLayout {
                spacing: 14

                QButton {
                    Layout.alignment: Qt.AlignHCenter
                    implicitWidth: 160
                    implicitHeight: 160
                    radius: width / 2
                    buttonStyle: QButton.ButtonStyle.Filled
                    backgroundColor: ThemeManager.theme.red
                    fontColor: ThemeManager.theme.white
                    image: "\uf011"
                    imageSize: 62
                    onClicked: root.submit("Shutdown")
                }

                QLabel {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Shutdown")
                    color: ThemeManager.theme.labelPrimary
                }
            }
        }

        QButton {
            Layout.alignment: Qt.AlignHCenter
            buttonStyle: QButton.ButtonStyle.Tinted
            backgroundColor: ThemeManager.theme.fillsSecondary
            fontColor: ThemeManager.theme.labelPrimary
            text: qsTr("Cancel")
            onClicked: root.close()
        }
    }
}
