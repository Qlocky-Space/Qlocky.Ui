import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts

Item {
    id: control

    property string icon
    property color color: ThemeManager.theme.labelPrimary
    property color dueColor: ThemeManager.theme.labelSecondary
    property real size: 32

    width: size
    height: size

    Text {
        anchors.fill: parent
        anchors.centerIn: parent
        z: 0

        text: icon.length === 2 ? icon[1] : null
        visible: icon.length === 2
        font.family: FontStyle.fontAwesome.family
        font.pixelSize: parent.height
        color: control.dueColor
    }

    Text {
        id: iconText
        z: 1

        anchors.fill: parent
        anchors.centerIn: parent

        text: icon.length > 0 ? icon[0] : null
        font.family: FontStyle.fontAwesome.family
        font.pixelSize: parent.height
        color: control.color
    }
}
