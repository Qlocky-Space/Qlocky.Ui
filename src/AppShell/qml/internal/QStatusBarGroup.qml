import QtQuick
import QtQuick.Layouts

import Ui

Item {
    id: root

    default property alias content: contentRow.data

    property bool rowMode: true
    property real spacing: 16

    // Set implicit size based on children
    implicitWidth: contentRow.implicitWidth + 40
    implicitHeight: contentRow.implicitHeight + 40

    QRoundedRectangle {
        anchors.fill: parent
        color: ThemeManager.theme.backgroundTertiary
        radius: 20
        cornerSide: QRoundedRectangle.Direction.All
    }

    GridLayout {
        id: contentRow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        flow: rowMode ? GridLayout.LeftToRight : GridLayout.TopToBottom
        columnSpacing: root.spacing
        rowSpacing: root.spacing

        // Children (QStatusBarIcon) will be placed here
    }
}