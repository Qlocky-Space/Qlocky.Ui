import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root

    required property string section

    width: 680
    height: 80

    // anchors {
    //     leftMargin: 16
    //     rightMargin: 16
    //     topMargin: 45
    //     bottomMargin: 7
    // }

    // Rectangle {
    //     color: "red"
    //     anchors.fill: parent
    // }

    QLabel {
        text: section
        font: FontStyle.caption

        color: ThemeManager.theme.labelSecondary
        anchors.bottom: parent.bottom
    }


}