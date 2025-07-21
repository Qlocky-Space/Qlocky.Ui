import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts

T.Button {
    id: control

    enum ButtonStyle {
        Filled,
        Tinted,
        Plain
    }

    property color backgroundColor: ThemeManager.theme.blue
    property color backgroundColorTinted: Qt.alpha(backgroundColor, 0.15)
    property color backgroundColorDisabled: ThemeManager.theme.miscellaneousButtonDisabled
    property color fontColorDisabled: ThemeManager.theme.labelTertiary
    property color fontColor: ThemeManager.theme.labelPrimary

    property real borderWidth: 0
    property color borderColor: "transparent"
    property int buttonStyle: QButton.ButtonStyle.Filled

    property string image: ""
    property real imageSize: Math.max(32, control.height * 0.8)

    property real radius: 40

    function getBackgroundColor() {
        if (!control.enabled) {
            return control.backgroundColorDisabled;
        }
        if (control.buttonStyle === QButton.ButtonStyle.Tinted) {
            return control.backgroundColorTinted;
        }
        if (control.buttonStyle === QButton.ButtonStyle.Plain) {
            return "transparent";
        }
        return control.backgroundColor;
    }

    function getFontColor() {
        if (!control.enabled) {
            return control.fontColorDisabled;
        }
        if (control.buttonStyle === QButton.ButtonStyle.Tinted) {
            return control.backgroundColor;
        }
        return control.fontColor;
    }

    font: FontStyle.caption
    padding: 10
    clip: true

    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding
    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding

    leftPadding: 12
    rightPadding: 12
    topPadding: 12
    bottomPadding: 12

    contentItem: Item {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter

        RowLayout {
            id: layout
            anchors.fill: parent
            spacing: 20

            QIcon {
                id: iconText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                icon: control.image
                color: control.getFontColor()
                size: control.imageSize
                visible: control.image !== "" && control.image !== null
            }

            QLabel {
                id: labelText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                text: control.text
                color: control.getFontColor()
                visible: control.text !== "" && control.text !== null
            }
        }

        implicitWidth: layout.implicitWidth
        implicitHeight: layout.implicitHeight
    }

    background: Rectangle {
        implicitHeight: control.implicitHeight
        implicitWidth: control.implicitWidth

        color: control.getBackgroundColor()
        radius: control.radius

        border.color: control.borderColor
        border.width: control.borderWidth

        visible: true
        layer.enabled: true
        layer.smooth: true
        clip: true

        Behavior on color {
            ColorAnimation {
                easing.type: Easing.Linear
                duration: 200
            }
        }

        Rectangle {
            id: indicator

            property int mx
            property int my
            x: mx - width / 2
            y: my - height / 2
            height: width
            radius: control.radius
            color: Qt.lighter(control.backgroundColor)
        }
    }

    Rectangle {
        id: mask
        radius: control.radius
        anchors.fill: parent
        visible: false
    }

    MouseArea {
        id: mouseArea
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
    }

    ParallelAnimation {
        id: main
        NumberAnimation {
            target: indicator
            properties: "width"
            from: 0
            to: control.width
            duration: 200
        }
        NumberAnimation {
            target: indicator
            properties: "opacity"
            from: 0.9
            to: 0
            duration: 200
        }
    }

    onPressed: {
        if (!control.enabled) {
            return;
        }

        indicator.mx = mouseArea.mouseX;
        indicator.my = mouseArea.mouseY;
        main.restart();
    }
}
