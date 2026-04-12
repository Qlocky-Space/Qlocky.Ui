import QtQuick
import QtQuick.Layouts

Item {
    id: root

    property bool running: true
    property string text: ""

    implicitWidth: content.implicitWidth
    implicitHeight: content.implicitHeight

    ColumnLayout {
        id: content
        anchors.centerIn: parent
        spacing: 10

        Item {
            Layout.alignment: Qt.AlignHCenter
            width: 48
            height: 48

            QIcon {
                id: spinnerIcon
                anchors.centerIn: parent
                icon: "\uf110"
                size: 42
                color: ThemeManager.theme.blue
            }

            RotationAnimator on rotation {
                target: spinnerIcon
                from: 0
                to: 360
                duration: 900
                loops: Animation.Infinite
                running: root.running
            }
        }

        QLabel {
            Layout.alignment: Qt.AlignHCenter
            text: root.text
            color: ThemeManager.theme.labelPrimary
            visible: text.length > 0
        }

        QLabel {
            Layout.alignment: Qt.AlignHCenter
            text: root.state
            color: ThemeManager.theme.labelSecondary
            visible: text.length > 0
        }
    }
}
