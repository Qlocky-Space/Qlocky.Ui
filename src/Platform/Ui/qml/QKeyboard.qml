import QtQuick.VirtualKeyboard
import QtQuick.VirtualKeyboard.Settings

InputPanel {
    id: inputPanel

    anchors.left: parent.left
    anchors.right: parent.right

    y: Qt.inputMethod.visible ? parent.height - inputPanel.height : parent.height

    z: 10000 // Ensure the input panel is always above other content
    focus: true
}