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
    property bool trailingClickable: false

    signal trailingClicked

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

        Item {
            id: trailingContainer
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            implicitWidth: trailingLoader.implicitWidth
            implicitHeight: trailingLoader.implicitHeight

            Loader {
                id: trailingLoader
                anchors.fill: parent

                sourceComponent: control.trailing
                active: control.trailing !== null
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: control.trailingClickable ? Qt.PointingHandCursor : Qt.ArrowCursor
                enabled: control.trailingClickable && control.trailing !== null
                onClicked: control.trailingClicked()
            }
        }
    }
}
