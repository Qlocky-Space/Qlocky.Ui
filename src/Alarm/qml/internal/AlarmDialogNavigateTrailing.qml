import QtQuick

import Ui

Row {
    id: root

    property string text: ""

    spacing: 10

    QLabel {
        text: root.text
        color: ThemeManager.theme.labelSecondary
        anchors.verticalCenter: parent.verticalCenter
    }

    QIcon {
        icon: "\uf054"
        color: ThemeManager.theme.labelSecondary
        anchors.verticalCenter: parent.verticalCenter
    }
}
