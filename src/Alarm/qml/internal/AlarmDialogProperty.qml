import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts

import Ui

Item {
    id: control

    property alias button: statusButton

    property string text: ""
    property bool status: false
    property string image: ""

    property Component trailing

    implicitHeight: layout.implicitHeight
    implicitWidth: layout.implicitWidth

    RowLayout {
        id: layout
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        QStatusButton {
            id: statusButton
            status: control.status

            image: control.image
        }

        QLabel {
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft

            text: control.text
        }

        Loader {
            id: trailingLoader
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            sourceComponent: control.trailing
            active: control.trailing !== null
        }
    }
}
