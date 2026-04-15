import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root

    required property string section

    width: 680
    height: 80

    QLabel {
        text: section
        font: FontStyle.caption

        color: ThemeManager.theme.labelSecondary
        anchors.bottom: parent.bottom
    }
}