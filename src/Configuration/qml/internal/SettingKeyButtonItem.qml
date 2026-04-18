import QtQuick
import QtQuick.Layouts

import Ui

SettingKeyValueBase {
    id: root

    property string text: ""

    clickable: true

    QButton {
        text: root.text
        buttonStyle: QButton.ButtonStyle.Tinted
        onClicked: root.clicked()
    }
}
