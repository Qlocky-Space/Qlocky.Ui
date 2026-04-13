import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    property var viewModel: RadioSourceSelectDialogViewModel

    Column {
        anchors.fill: parent
        spacing: 20

        RowLayout {
            width: parent.width
            spacing: 12

            QTextField {
                id: searchField
                Layout.fillWidth: true
                hint: qsTr("Search by name")
                currentText: viewModel.searchText
                clearTextButtonVisible: true

                onTextEdited: function(text) {
                    viewModel.searchText = text;
                }

                onAccepted: {
                    viewModel.search();
                }

                onTextCleared: {
                    viewModel.searchText = "";
                }
            }

            QButton {
                Layout.preferredWidth: 64
                Layout.preferredHeight: 64
                buttonStyle: QButton.ButtonStyle.Tinted
                image: ""
                enabled: viewModel.searchText.trim().length > 0 && !viewModel.searching

                onClicked: {
                    viewModel.search();
                }
            }
        }

        QBusyIndicator {
            anchors.horizontalCenter: parent.horizontalCenter
            running: viewModel.searching
            visible: viewModel.searching
            text: qsTr("Searching Stations")
            state: viewModel.searchText
        }

        QLabel {
            visible: !viewModel.searching && viewModel.searched && viewModel.searchResults.length === 0
            text: qsTr("No stations found.")
            color: ThemeManager.theme.labelSecondary
            anchors.horizontalCenter: parent.horizontalCenter
        }

        ListView {
            id: resultList
            width: parent.width
            height: parent.height - y
            clip: true
            spacing: 12
            model: viewModel.searchResults
            visible: !viewModel.searching && viewModel.searchResults.length > 0

            delegate: RadioSourceItem {
                required property var modelData

                width: resultList.width
                stationId: modelData.id
                stationName: modelData.name
                votes: modelData.votes
                favicon: modelData.favicon
                secondaryText: modelData.language.length > 0 ? modelData.language : qsTr("Unknown language")
                selected: viewModel.selectedSource === modelData.id
                showVotes: true
                showFavoriteAction: true
                isFavorite: modelData.isFavorite

                onClicked: {
                    viewModel.selectedSource = modelData.id;
                }

                onFavoriteClicked: {
                    viewModel.toggleFavorite(modelData.id);
                }
            }
        }
    }
}
