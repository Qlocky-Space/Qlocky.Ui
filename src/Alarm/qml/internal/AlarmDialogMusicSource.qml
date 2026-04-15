import QtQuick
import QtQuick.Layouts

import Ui

Item {
    id: root

    required property var alarm

    property var viewModel: AlarmMusicSourceViewModel
    property int currentPage: 0

    implicitWidth: 1000
    implicitHeight: 670

    signal done

    readonly property var pageItems: [
        {
            resourceUri: "/qt/qml/Radio/qml/internal/RadioSourceFavorites.qml",
            icon: "\uf004",
            text: qsTr("Favorites")
        },
        {
            resourceUri: "/qt/qml/Radio/qml/internal/RadioSourceSearch.qml",
            icon: "\uf002",
            text: qsTr("Search")
        },
        {
            resourceUri: "/qt/qml/Radio/qml/internal/RadioSourceLibrary.qml",
            icon: "\uf07c",
            text: qsTr("Your Library")
        }
    ]

    function selectedName() {
        for (let i = 0; i < viewModel.searchResults.length; ++i) {
            const station = viewModel.searchResults[i];
            if (station.id === viewModel.selectedSource) {
                return station.name;
            }
        }

        for (let j = 0; j < viewModel.favorites.length; ++j) {
            const favorite = viewModel.favorites[j];
            if (favorite.id === viewModel.selectedSource) {
                return favorite.name;
            }
        }

        return "";
    }

    function confirmSelection() {
        const name = root.selectedName();
        root.alarm.musicSourceId = viewModel.selectedSource;
        root.alarm.musicSourceName = name.length > 0 ? name : root.alarm.musicSourceName;
        root.done();
    }

    Component.onCompleted: {
        currentPage = 0;
        viewModel.resetSelection();

        if (alarm.musicSourceId.length > 0) {
            viewModel.selectedSource = alarm.musicSourceId;
        }
    }

    Column {
        anchors.fill: parent
        spacing: 0

        Loader {
            id: pageLoader
            width: parent.width
            height: parent.height - bottomMenu.height
            source: root.pageItems[root.currentPage].resourceUri

            onLoaded: {
                if (item && item.viewModel !== undefined) {
                    item.viewModel = root.viewModel;
                }
            }
        }

        QBottomNavigation {
            id: bottomMenu
            width: parent.width
            height: 120

            items: root.pageItems
            currentIndex: root.currentPage

            onItemSelected: {
                root.currentPage = index;
            }
        }
    }
}
