import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

QDialog {
    id: root

    property var viewModel: RadioSourceSelectDialogViewModel
    property int currentPage: 1

    implicitWidth: 1000
    implicitHeight: 850
    acceptText: qsTr("Choose")

    onOpened: {
        currentPage = 1;
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

            source: {
                switch (root.currentPage) {
                    case 0:
                        return "internal/RadioSourceFavorites.qml";
                    case 2:
                        return "internal/RadioSourceLibrary.qml";
                    default:
                        return "internal/RadioSourceSearch.qml";
                }
            }
        }

        Rectangle {
            id: bottomMenu
            width: parent.width
            height: 120
            radius: 28
            color: Qt.darker(ThemeManager.theme.fillsSecondary, 1.08)

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 24
                anchors.rightMargin: 24
                spacing: 10

                Repeater {
                    model: [
                        { title: qsTr("Favorites"), icon: "\uf004" },
                        { title: qsTr("Search"), icon: "\uf002" },
                        { title: qsTr("Your Library"), icon: "\uf07c" }
                    ]

                    delegate: Item {
                        required property var modelData
                        required property int index

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        readonly property bool selected: root.currentPage === index
                        readonly property color itemColor: selected
                            ? ThemeManager.theme.labelPrimary
                            : ThemeManager.theme.labelSecondary

                        Column {
                            anchors.centerIn: parent
                            spacing: 8

                            QIcon {
                                anchors.horizontalCenter: parent.horizontalCenter
                                icon: modelData.icon
                                size: 35
                                color: parent.parent.itemColor
                            }

                            QLabel {
                                text: modelData.title
                                color: parent.parent.itemColor
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor

                            onClicked: {
                                root.currentPage = index;
                            }
                        }
                    }
                }
            }
        }
    }
}
