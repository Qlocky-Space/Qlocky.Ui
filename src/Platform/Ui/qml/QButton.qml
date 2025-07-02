import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts

T.Button {
    id: control

    property color backgroundColor: ThemeManager.theme.blue
    property real borderWidth: 0
    property color borderColor: "transparent"

    property string image: ""
    property color textColor: ThemeManager.theme.labelPrimary

    property real radius: 40

    font: FontStyle.caption
    padding: 10
    clip: true

    implicitHeight: contentItem.implicitHeight + topPadding + bottomPadding
    implicitWidth: contentItem.implicitWidth + leftPadding + rightPadding

    leftPadding: 16
    rightPadding: 16

    contentItem: Item {
        width: parent.width
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter

        RowLayout {
            id: layout
            anchors.fill: parent
            spacing: 20

            Text {
                id: iconText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                text: control.image
                font.family: FontStyle.fontAwesome.family
                font.pixelSize: Math.max(32, parent.height * 0.8)
                color: control.enabled ? control.textColor : ThemeManager.theme.labelTertiary
                visible: control.image !== "" && control.image !== null
            }

            T.Label {
                id: labelText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                font: control.font
                text: control.text
                color: control.enabled ? control.textColor : ThemeManager.theme.labelTertiary
                visible: control.text !== "" && control.text !== null
            }
        }

        implicitWidth: layout.implicitWidth
        implicitHeight: layout.implicitHeight
    }

    background: Rectangle {
        implicitHeight: control.implicitHeight
        implicitWidth: control.implicitWidth

        color: control.enabled ? control.backgroundColor : ThemeManager.theme.fillsTertiary
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
            x: mx - width/2
            y: my - height/2
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
        if (!control.enabled) { return; }

        indicator.mx = mouseArea.mouseX
        indicator.my = mouseArea.mouseY
        main.restart()
    }
}
