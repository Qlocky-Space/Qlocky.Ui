import QtQuick
import QtQuick.Layouts

import Ui

Item {
    property var viewModel: RadioSourceSelectDialogViewModel

    Item {
        anchors.fill: parent

        Column {
            anchors.centerIn: parent
            spacing: 16
            visible: viewModel.favorites.length === 0

            QIcon {
                anchors.horizontalCenter: parent.horizontalCenter
                icon: ""
                size: 54
                color: ThemeManager.theme.labelPrimary
            }

            QLabel {
                text: qsTr("Favorites")
                anchors.horizontalCenter: parent.horizontalCenter
            }

            QLabel {
                text: qsTr("Your favorite radio sources will appear here.")
                color: ThemeManager.theme.labelSecondary
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        ListView {
            id: favoritesList
            anchors.fill: parent
            clip: true
            spacing: 12
            model: viewModel.favorites
            visible: viewModel.favorites.length > 0

            delegate: RadioSourceItem {
                required property var modelData

                width: favoritesList.width
                stationId: modelData.id
                stationName: modelData.name
                favicon: modelData.favicon
                secondaryText: modelData.provider
                selected: viewModel.selectedSource === modelData.id
                showVotes: false
                showFavoriteAction: true
                isFavorite: true

                onClicked: {
                    viewModel.selectedSource = modelData.id;
                }

                onFavoriteClicked: {
                    viewModel.removeFavorite(modelData.id);
                }
            }
        }
    }
}
