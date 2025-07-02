import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts

Item {
    id: control

    property string icon
    property color color: ThemeManager.theme.labelPrimary
    property real size: 32

    width: size
    height: size

    Text {
        id: iconText

        anchors.fill: parent
        anchors.centerIn: parent

        text: control.icon
        font.family: FontStyle.fontAwesome.family
        font.pixelSize: parent.height
        color: control.color
    }
}
