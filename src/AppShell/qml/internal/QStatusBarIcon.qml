import QtQuick
import QtQuick.Layouts

import Ui

RowLayout {
    id: root

    property string icon
    property string iconInactive: icon

    property string title
    property string description
    property bool isActive: false

    readonly property bool showDescription: !(!title || !description)

    signal clicked(bool state)

    spacing: 0

    QStatusButton {
        id: button
        Layout.alignment: Qt.AlignVCenter

        status: root.isActive
        image: root.icon
        imageInactive: root.iconInactive

        onClicked: {
            root.clicked(!root.isActive)
        }
    }

    ColumnLayout {
        id: description
        visible: root.showDescription

        spacing: 2
        Layout.alignment: Qt.AlignVCenter
        Layout.leftMargin: 20
        Layout.fillWidth: true

        QLabel {
            text: root.title

            color: ThemeManager.theme.labelPrimary
            elide: Text.ElideRight

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }

        QLabel {
            text: root.description
            visible: root.description !== ""

            color: ThemeManager.theme.labelSecondary
            font: FontStyle.subCaption
            elide: Text.ElideRight

            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        }
    }
}