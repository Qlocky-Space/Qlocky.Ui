import QtQuick
import QtQuick.Layouts

import Ui

Item {
    id: root

    default property alias content: contentRow.data

    // Set implicit size based on children
    implicitWidth: contentRow.implicitWidth + 40
    implicitHeight: contentRow.implicitHeight + 40

    QRoundedRectangle {
        anchors.fill: parent
        color: ThemeManager.theme.backgroundTertiary
        radius: 20
        cornerSide: QRoundedRectangle.Direction.All
    }

    RowLayout {
        id: contentRow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 16

        // Children (QStatusBarIcon) will be placed here
    }
}