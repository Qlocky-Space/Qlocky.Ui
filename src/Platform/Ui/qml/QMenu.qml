import QtQuick
import QtQuick.Controls as T
import QtQuick.Layouts

import Ui

T.Menu {
    id: menu

    topPadding: 8
    bottomPadding: 8

    delegate: QMenuItem {}

    background: Rectangle {
        implicitWidth: 400
        implicitHeight: 100

        color: ThemeManager.theme.backgroundSecondary
        border.color: ThemeManager.theme.backgroundPrimary
        radius: 8
    }
}