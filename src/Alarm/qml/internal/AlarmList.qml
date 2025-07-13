import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    id: root

    property var model

    ListView  {
        id: listView
        snapMode: ListView.SnapOneItem
        anchors.fill: parent
        clip: true

        model: root.model

        delegate: AlarmListItem {
            required property AlarmItemViewModel modelData

            width: listView.width
            model: modelData
        }
    }
}