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
    property string language: ""
    property bool selected: false

    signal clicked()

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
        anchors.fill: parent
        anchors.leftMargin: 18
        anchors.rightMargin: 18
        spacing: 16

        // Icon
        Item {
            Layout.preferredWidth: 55
            Layout.preferredHeight: 55

            // Loading image
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

            // The real icon
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

            // Station name
            QLabel {
                Layout.fillWidth: true
                text: stationName
                color: ThemeManager.theme.labelPrimary
                elide: Text.ElideRight
            }

            // Details
            RowLayout {
                Layout.fillWidth: true
                spacing: 16

                QLabel {
                    text: qsTr("Votes: %1").arg(votes)
                    color: ThemeManager.theme.labelSecondary
                    font.pixelSize: 32
                }

                QLabel {
                    Layout.fillWidth: true
                    text: language.length > 0 ? language : qsTr("Unknown language")
                    color: ThemeManager.theme.labelSecondary
                    elide: Text.ElideRight
                    font.pixelSize: 32
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: root.clicked()
    }
}
