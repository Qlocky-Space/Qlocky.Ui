import QtQuick

import Ui

QDialog {
    id: root

    property var viewModel: RadioSourceSelectDialogViewModel
    property int currentPage: 0
    readonly property var pageItems: [
        {
            resourceUri: "internal/RadioSourceFavorites.qml",
            icon: "\uf004",
            text: qsTr("Favorites")
        },
        {
            resourceUri: "internal/RadioSourceSearch.qml",
            icon: "\uf002",
            text: qsTr("Search")
        },
        {
            resourceUri: "internal/RadioSourceLibrary.qml",
            icon: "\uf07c",
            text: qsTr("Your Library")
        }
    ]

    implicitWidth: 1000
    implicitHeight: 850
    acceptText: qsTr("Choose")

    onOpened: {
        currentPage = 0;
        viewModel.resetSelection();
    }

    onCanceled: {
        close();
    }

    onAccepted: {
        viewModel.chooseSelectedStation();
        close();
    }

    Column {
        id: content
        anchors.fill: parent
        spacing: 0

        Loader {
            id: pageLoader
            width: parent.width
            height: parent.height - bottomMenu.height - parent.spacing

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
