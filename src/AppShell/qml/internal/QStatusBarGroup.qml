import QtQuick
import QtQuick.Layouts

import Ui

Item {
    id: root

    default property alias content: contentRow.data

    property bool rowMode: true
    property real spacing: 20

    // Set implicit size based on children
    implicitWidth: contentRow.implicitWidth + spacing * 2
    implicitHeight: contentRow.implicitHeight + spacing * 2

    QRoundedRectangle {
        anchors.fill: parent
        color: ThemeManager.theme.backgroundTertiary
        radius: 20
        cornerSide: QRoundedRectangle.Direction.All
    }

    GridLayout {
        id: contentRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: root.spacing
        anchors.verticalCenter: parent.verticalCenter
        flow: rowMode ? GridLayout.LeftToRight : GridLayout.TopToBottom
        columnSpacing: root.spacing
        rowSpacing: root.spacing

        // Children (QStatusBarIcon) will be placed here
    }
}