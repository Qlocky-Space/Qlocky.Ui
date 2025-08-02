import QtQuick
import QtQuick.Layouts

import Ui

SettingKeyValueBase {
    id: root

    property string value: ""

    QLabel {
        text: root.value
        color: ThemeManager.theme.labelSecondary
    }
}