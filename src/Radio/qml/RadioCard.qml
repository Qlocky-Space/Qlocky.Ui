import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Widget
import Ui

Widget {
    id: card
    color: "transparent"
    radius: 34

    property var viewModel: RadioCardViewModel

    readonly property bool showTransportControls: viewModel.hasSelection && viewModel.isControllable
    readonly property bool showPlayPauseControl: viewModel.hasSelection

    Rectangle {
        anchors.fill: parent
        radius: card.radius
        clip: true
        color: ThemeManager.theme.fillsSecondary

        // Left artwork panel (click opens source dialog)
        Rectangle {
            id: artworkPanel
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            width: Math.round(parent.width * 0.34)
            color: ThemeManager.theme.backgroundSecondary

            Rectangle {
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.alpha(ThemeManager.theme.backgroundSecondary, 0.15) }
                    GradientStop { position: 1.0; color: Qt.alpha(ThemeManager.theme.backgroundSecondary, 0.55) }
                }
            }

            Image {
                id: stationArtwork
                anchors.fill: parent
                source: viewModel.iconUrl
                fillMode: Image.PreserveAspectCrop
                asynchronous: true
                cache: true
                visible: source.toString().length > 0 && status === Image.Ready
            }

            Rectangle {
                anchors.fill: parent
                color: Qt.alpha(ThemeManager.theme.backgroundSecondary, 0.32)
            }

            QIcon {
                anchors.centerIn: parent
                icon: "\uf001"
                size: Math.min(parent.width, parent.height) * 0.32
                color: Qt.alpha(ThemeManager.theme.labelPrimary, 0.7)
                visible: !stationArtwork.visible
            }

            // Playback controls
            Row {
                id: controls
                spacing: 40
                anchors.centerIn: parent

                QButton {
                    width: 80
                    height: 80
                    buttonStyle: QButton.ButtonStyle.Plain
                    image: "\uf048"
                    imageSize: 72
                    visible: card.showTransportControls
                    onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://radioSourceSelectDialog" })
                }

                QButton {
                    width: 80
                    height: 80
                    buttonStyle: QButton.ButtonStyle.Plain
                    image: viewModel.playing ? "\uf04c" : "\uf04b"
                    imageSize: 72
                    visible: card.showPlayPauseControl
                    onClicked: viewModel.togglePlayback()
                }

                QButton {
                    width: 80
                    height: 80
                    buttonStyle: QButton.ButtonStyle.Plain
                    image: "\uf051"
                    imageSize: 72
                    visible: card.showTransportControls
                    onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://radioSourceSelectDialog" })
                }
            }

            MouseArea {
                enabled: !card.showPlayPauseControl
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://radioSourceSelectDialog" })
            }
        }

        // Right side blend for readable text and controls
        Rectangle {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: artworkPanel.right
            anchors.right: parent.right
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.alpha(ThemeManager.theme.backgroundSecondary, 0.05) }
                GradientStop { position: 1.0; color: Qt.alpha(ThemeManager.theme.backgroundSecondary, 0.40) }
            }
        }

        // Top-right actions
        Row {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 20
            anchors.rightMargin: 20
            spacing: 18

            Item {
                width: 60
                height: 60
                visible: card.showPlayPauseControl

                QIcon {
                    anchors.centerIn: parent
                    icon: viewModel.favorite ? "\u2665" : "\u2661"
                    size: 52
                    color: ThemeManager.theme.white
                }

                MouseArea {
                    anchors.fill: parent
                    enabled: card.showPlayPauseControl
                    cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
                    onClicked: viewModel.toggleFavorite()
                }
            }

            Item {
                width: 60
                height: 60

                QIcon {
                    anchors.centerIn: parent
                    icon: "\uf0c9"
                    size: 52
                    color: ThemeManager.theme.labelPrimary
                }

                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: CommandExecutor.dispatch("nav-to", { "uri": "qlocky://radioSourceSelectDialog" })
                }
            }
        }

        // Main content
        Column {
            id: content
            spacing: 24

            anchors.left: artworkPanel.right
            anchors.right: parent.right
            anchors.leftMargin: 26
            anchors.rightMargin: 26
            anchors.verticalCenter: parent.verticalCenter

            Column {
                width: parent.width - 110
                spacing: 6

                Text {
                    width: parent.width
                    text: viewModel.title
                    elide: Text.ElideRight
                    color: ThemeManager.theme.labelPrimary
                    font.bold: true
                    font.pixelSize: 52
                }

                Text {
                    width: parent.width
                    text: viewModel.subtitle
                    elide: Text.ElideRight
                    color: ThemeManager.theme.labelSecondary
                    font.pixelSize: 30
                }
            }

            // Progress / status
            Column {
                width: parent.width
                spacing: 14
                visible: card.showTransportControls

                Rectangle {
                    width: parent.width
                    height: 8
                    radius: height / 2
                    color: ThemeManager.theme.fillsTertiary

                    Rectangle {
                        width: viewModel.playing ? parent.width * 0.35 : 0
                        height: parent.height
                        radius: parent.radius
                        color: ThemeManager.theme.fillsPrimary
                    }
                }

                Text {
                    text: viewModel.playing ? qsTr("Playing") : qsTr("Ready")
                    color: ThemeManager.theme.labelSecondary
                    font.pixelSize: 20
                }
            }
        }
    }
}
