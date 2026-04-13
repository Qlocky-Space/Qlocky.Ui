import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    id: root

    property string stationId: ""
    property string stationName: ""
    property int votes: 0
    property string favicon: ""
    property string secondaryText: ""
    property bool selected: false
    property bool showVotes: true
    property bool showFavoriteAction: false
    property bool isFavorite: false

    signal clicked()
    signal favoriteClicked()

    implicitWidth: parent ? parent.width : 0
    implicitHeight: 100

    Rectangle {
        anchors.fill: parent
        radius: 20
        color: selected ? Qt.alpha(ThemeManager.theme.blue, 0.16) : ThemeManager.theme.miscellaneousTextFieldBackground
        border.width: selected ? 2 : 1
        border.color: selected ? ThemeManager.theme.blue : ThemeManager.theme.miscellaneousTextFieldOutline
    }

    RowLayout {
        z: 1
        anchors.fill: parent
        anchors.leftMargin: 18
        anchors.rightMargin: 18
        spacing: 16

        Item {
            Layout.preferredWidth: 55
            Layout.preferredHeight: 55

            Rectangle {
                anchors.fill: parent
                radius: width / 2
                color: Qt.darker(ThemeManager.theme.fillsSecondary, 1.08)
                visible: stationIcon.status !== Image.Ready
            }

            QIcon {
                anchors.centerIn: parent
                icon: "\uf001"
                size: 24
                color: ThemeManager.theme.labelSecondary
                visible: stationIcon.status !== Image.Ready
            }

            Image {
                id: stationIcon
                anchors.fill: parent
                source: favicon
                fillMode: Image.PreserveAspectFit
                asynchronous: true
                cache: true
                visible: status === Image.Ready
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            QLabel {
                Layout.fillWidth: true
                text: stationName
                color: ThemeManager.theme.labelPrimary
                elide: Text.ElideRight
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 16

                QLabel {
                    visible: root.showVotes
                    text: qsTr("Votes: %1").arg(votes)
                    color: ThemeManager.theme.labelSecondary
                    font.pixelSize: 32
                }

                QLabel {
                    Layout.fillWidth: true
                    text: secondaryText
                    color: ThemeManager.theme.labelSecondary
                    elide: Text.ElideRight
                    font.pixelSize: 32
                }
            }
        }

        Item {
            z: 2
            Layout.preferredWidth: showFavoriteAction ? 42 : 0
            Layout.preferredHeight: 42
            visible: showFavoriteAction

            QIcon {
                anchors.centerIn: parent
                icon: "\uf004"
                size: 28
                color: isFavorite ? ThemeManager.theme.pink : ThemeManager.theme.labelSecondary
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: function(mouse) {
                    mouse.accepted = true;
                    root.favoriteClicked();
                }
            }
        }
    }

    MouseArea {
        z: 0
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}