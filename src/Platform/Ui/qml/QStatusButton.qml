import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts

T.Button {
    id: control

    property color backgroundColor: ThemeManager.theme.blue
    property color backgroundColorDisabled: ThemeManager.theme.miscellaneousButtonDisabled
    property color fontColorDisabled: ThemeManager.theme.labelTertiary
    property color fontColor: ThemeManager.theme.labelPrimary

    property real borderWidth: 0
    property color borderColor: "transparent"

    property string image: ""

    property bool status: false
    property real radius:20

    function getBackgroundColor() {
        if (!control.status) {
            return control.backgroundColorDisabled;
        }
        return control.backgroundColor;
    }

    function getFontColor() {
        if (!control.status) {
            return control.fontColorDisabled;
        }
        return control.fontColor;
    }

    font: FontStyle.caption
    padding: 10
    clip: true

    height: 100
    width: 100

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
                size: Math.max(32, parent.height * 0.4)
                visible: control.image !== "" && control.image !== null
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
    }

    Rectangle {
        id: mask
        radius: control.radius
        anchors.fill: parent
        visible: false
    }
}
