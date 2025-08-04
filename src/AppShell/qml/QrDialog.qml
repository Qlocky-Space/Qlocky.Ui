import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

QDialog {
    id: root

    property string content

    implicitWidth: 800
    implicitHeight: 800

    cancelShow: false
    acceptText: qsTr("Close")

    onAccepted: {
        close();
    }

    Rectangle {
        id: qrImage

        anchors.centerIn: parent

        height: 500
        width: 500
        Image {
            anchors.fill: parent
            source: "image://qr/" + root.content
            fillMode: Image.PreserveAspectFit
        }
    }
}
