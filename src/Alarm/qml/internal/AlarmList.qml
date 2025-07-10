import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    ListView  {
        id: listView
        snapMode: ListView.SnapOneItem
        anchors.fill: parent
        clip: true

        model: 15
        delegate: AlarmListItem {
            width: listView.width
        }
    }
}