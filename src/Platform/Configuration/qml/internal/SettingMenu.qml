import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root

    property alias model: settingListView.model
    property int selectedIndex: 0

    signal settingSelected(int index)

    onSelectedIndexChanged: {
        settingListView.currentIndex = selectedIndex
        settingListView.positionViewAtIndex(selectedIndex, ListView.Beginning)
    }

    ListView {
        id: settingListView
        anchors {
            margins: 50
            bottomMargin: 10

            fill: parent
        }

        section.property: "category"
        section.criteria: ViewSection.FullString
        section.delegate: SettingMenuHeader {}
        section.labelPositioning: ViewSection.InlineLabels

        highlightMoveDuration: 100

        spacing: 0
        clip: true
        focus: true
        delegate: SettingMenuItem {
            onClicked: {
                settingListView.currentIndex = index
                root.settingSelected(index)
            }
        }
        highlight: Rectangle {
            color: ThemeManager.theme.fillsPrimary
            radius: 20
        }
    }
}