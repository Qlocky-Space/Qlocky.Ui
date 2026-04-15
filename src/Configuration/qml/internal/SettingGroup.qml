import QtQuick
import QtQuick.Layouts

import Ui

Item {
    id: root

    default property alias content: contentRow.data

    property bool rowMode: false
    property string title: ""
    property real spacing: 1

    // Set implicit size based on children
    implicitWidth: contentContainer.implicitWidth
    implicitHeight: contentContainer.implicitHeight + titleLabel.height
    clip: true

    QLabel {
        id: titleLabel
        height: 80

        text: root.title

        font: FontStyle.caption
        color: ThemeManager.theme.labelSecondary

        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.top: parent.top
        anchors.topMargin: 45
    }

    Item {
        id: contentContainer
        // Set implicit size based on children
        implicitWidth: contentRow.implicitWidth + (spacing + contentRow.anchors.margins) * 2
        implicitHeight: contentRow.implicitHeight + (spacing + contentRow.anchors.margins) * 2

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: titleLabel.bottom
        anchors.bottom: parent.bottom

        QRoundedRectangle {
            anchors.fill: parent
            color: ThemeManager.theme.backgroundSecondary
            radius: 20
            cornerSide: QRoundedRectangle.Direction.All
        }

        GridLayout {
            id: contentRow
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 20
            anchors.verticalCenter: parent.verticalCenter

            flow: rowMode ? GridLayout.LeftToRight : GridLayout.TopToBottom
            columnSpacing: root.spacing
            rowSpacing: root.spacing

            // Children (QStatusBarIcon) will be placed here
        }
    }
}