import QtQuick
import QtQuick.Controls as T
import QtQuick.Layouts

import Ui

T.MenuSeparator {
    contentItem: Rectangle {
        implicitWidth: 400
        implicitHeight: 2
        color: ThemeManager.theme.miscellaneousSeperatorOpaque
    }
}