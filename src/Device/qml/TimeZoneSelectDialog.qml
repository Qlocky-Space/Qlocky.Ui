import QtQuick
import QtQuick.Layouts

import Ui

QDialog {
    id: root

    property var viewModel: AppearanceViewModel
    property string filterText: ""

    readonly property var filteredGroups: {
        const filter = root.filterText.trim().toLowerCase();
        const groups = root.viewModel.timeZoneGroups;
        if (filter.length === 0) {
            return groups;
        }
        return groups.filter(group => group.searchText.includes(filter));
    }

    readonly property var pickerEntries: root.filteredGroups.map(group => group.offset + "   " + group.cities)

    implicitWidth: 1000
    implicitHeight: 850
    acceptText: qsTr("Choose")

    // Keeps the wheel on the selected group, or selects the first visible group
    // if the selection is filtered out, so "Choose" always applies what is shown.
    function syncSelection() {
        if (root.filteredGroups.length === 0) {
            return;
        }
        const index = root.filteredGroups.findIndex(group => group.id === root.viewModel.selectedTimeZoneGroup);
        if (index >= 0) {
            picker.currentIndex = index;
        } else {
            picker.currentIndex = 0;
            root.viewModel.selectedTimeZoneGroup = root.filteredGroups[0].id;
        }
    }

    onFilteredGroupsChanged: Qt.callLater(root.syncSelection)

    onOpened: {
        root.filterText = "";
        searchField.currentText = "";
        root.viewModel.resetTimeZoneSelection();
        Qt.callLater(root.syncSelection);
    }

    onCanceled: {
        close();
    }

    onAccepted: {
        root.viewModel.applySelectedTimeZone();
        close();
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 16

        QTextField {
            id: searchField
            Layout.fillWidth: true
            hint: qsTr("Search by city or UTC offset")
            clearTextButtonVisible: true

            onTextEdited: function (text) {
                root.filterText = text;
            }
            onTextCleared: {
                root.filterText = "";
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            QPicker {
                id: picker
                anchors.fill: parent
                visible: root.filteredGroups.length > 0

                model: root.pickerEntries
                visibleRows: 5
                horizontalAlignment: Text.AlignLeft
                textMargin: 20
                fontPixelSize: Math.min(rowHeight * 0.5, 40)

                onSelected: function (index) {
                    root.viewModel.selectedTimeZoneGroup = root.filteredGroups[index].id;
                }
            }

            QLabel {
                anchors.centerIn: parent
                visible: root.filteredGroups.length === 0
                text: qsTr("No time zone found")
                color: ThemeManager.theme.labelSecondary
            }
        }
    }
}
