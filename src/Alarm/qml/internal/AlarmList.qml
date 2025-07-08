import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    ScrollView  {
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent

            Repeater {
                model: 15
                delegate: AlarmListItem {
                    Layout.fillWidth: true
                }
            }
        }
    }
}