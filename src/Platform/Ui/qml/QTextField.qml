import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic as Controls
import QtQuick.VirtualKeyboard

import Ui

FocusScope {
    id: root

    property string currentText: ""

    property alias validator: valueInput.validator
    property alias maximumLength: valueInput.maximumLength

    property alias hint: valueInput.placeholderText
    property bool clearTextButtonVisible: false

    property alias textHorizontalAlignment: valueInput.horizontalAlignment
    property alias textVerticalAlignment: valueInput.verticalAlignment
    property bool hasText: valueInput.text.length > 0
    property alias readOnly: valueInput.readOnly

    property real textSidePadding: 12
    property real accessoriesPadding: 4

    readonly property alias inputField: valueInput
    readonly property alias background: background

    readonly property alias clearTextButton: clearTextButtonItem

    implicitHeight: 64
    implicitWidth: parent.width

    opacity: root.enabled ? 1.0 : ui.theme.itemOpacityDisabled

    signal textChanged(var newTextValue)
    signal textEdited(var newTextValue)
    signal textCleared()
    signal textEditingFinished(var newTextValue)
    signal accepted()
    signal escaped()

    function selectAll() {
        valueInput.selectAll()
    }

    function clear() {
        valueInput.text = ""
        currentText = ""
        root.textCleared()
    }

    Rectangle {
        id: background
        anchors.fill: parent

        color: ThemeManager.theme.miscellaneousTextFieldBackground
        border.width: 1
        border.color: root.activeFocus ? ThemeManager.theme.blue : ThemeManager.theme.miscellaneousTextFieldOutline
        radius: 3
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: root.textSidePadding
        anchors.rightMargin: clearTextButtonItem.visible ? 0 : root.textSidePadding

        Controls.TextField {
            id: valueInput
            objectName: "TextField"

            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            padding: 0

            color: ThemeManager.theme.labelPrimary
            font: FontStyle.caption

            background: Item {}

            focus: true
            activeFocusOnPress: true
            selectByMouse: true
            selectionColor: ThemeManager.theme.miscellaneousTextFieldTinted
            selectedTextColor: color
            placeholderTextColor: ThemeManager.theme.labelTertiary

            text: root.currentText

            Keys.onPressed: function(event) {
                var isAcceptKey = event.key === Qt.Key_Enter || event.key === Qt.Key_Return
                var isEscapeKey = event.key === Qt.Key_Escape

                if (isAcceptKey) {
                    root.accepted()
                }

                if (isEscapeKey) {
                    root.escaped()
                }

                if (isAcceptKey || isEscapeKey) {
                    root.focus = false
                }
            }

            onActiveFocusChanged: {
                if (activeFocus) {
                    selectAll()
                } else {
                    deselect()
                }
            }

            onTextChanged: {
                if (!acceptableInput) {
                    return
                }

                root.textChanged(text)
            }

            onTextEdited: {
                if (!acceptableInput) {
                    return
                }

                root.textEdited(text)
            }

            onEditingFinished: {
                root.textEditingFinished(valueInput.text)
            }
        }

        QButton {
            id: clearTextButtonItem

            Layout.fillHeight: true
            Layout.preferredWidth: height
            Layout.margins: root.accessoriesPadding
            focus: false

            buttonStyle: QButton.ButtonStyle.Plain

            visible: root.hasText && root.clearTextButtonVisible
            image: "\uf00d"

            onClicked: {
                root.clear()
            }
        }
    }

}
