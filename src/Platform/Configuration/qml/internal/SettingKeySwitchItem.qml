import QtQuick
import QtQuick.Layouts

import Ui

SettingKeyValueBase {
    id: root

    property bool value: false

    signal toggled(bool checked)

    QToggleButton {
        checked: root.value
        onToggled: function(checked) {
            root.toggled(checked)
        }
    }
}