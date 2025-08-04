import QtQuick
import QtQuick.Layouts

import Ui
import Configuration

SettingKeyValueBase {
    id: root

    required property int signalStrength

    QLabel {
        text: signalStrength + " dBm"
        color: root.titleColor
    }
}