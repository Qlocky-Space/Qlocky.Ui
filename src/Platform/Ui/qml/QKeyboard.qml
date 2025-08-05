import QtQuick
import QtQuick.Effects
import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Settings

import Ui

Item {
    z: 10000 // Ensure the input panel is always above other content

    anchors.fill: parent
    property alias input: inputPanel

    InputPanel {
        id: inputPanel

        width: parent.width

        y: Qt.inputMethod.visible ? parent.height - inputPanel.height : parent.height

        // TODO based on LanguageService.cpp, set the locale dynamically
        Component.onCompleted: {
            VirtualKeyboardSettings.locale = Qt.locale().name;
        }
    }
}