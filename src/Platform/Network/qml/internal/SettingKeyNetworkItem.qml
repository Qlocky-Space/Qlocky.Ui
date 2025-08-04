import QtQuick
import QtQuick.Layouts

import Ui
import Configuration

SettingKeyValueBase {
    id: root

    required property string ssid
    required property bool connected
    required property int signalStrength

    QLabel {
        text: root.ssid
        color: ThemeManager.theme.labelSecondary
    }
}