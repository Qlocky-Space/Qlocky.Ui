import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    height: 12
    width: 460

    QRoundedRectangle {
        anchors.fill: parent
        cornerSide: QRoundedRectangle.Direction.All
        radius: 6
        color: ThemeManager.theme.white
    }
}