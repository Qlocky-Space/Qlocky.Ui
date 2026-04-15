import QtQuick
import QtQuick.Layouts

import Ui

SettingKeyValueBase {
    id: root

    property string value: ""

    property alias valueLabel: label

    QLabel {
        id: label
        text: root.value
        color: ThemeManager.theme.labelSecondary
    }
}