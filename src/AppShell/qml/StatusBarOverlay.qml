import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import Ui

Item {
    property var viewModel: StatusBarViewModel

    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 20

        // TODO extract into sepearte component and may replace it with a Drawer?
        QButton {
            image: "\uf1b9"
            text: "To Settings"
            Layout.alignment: Qt.AlignHCenter

            onClicked: {
                CommandExecutor.dispatch("nav-to", {
                    "uri": "qlocky://settings"
                });
            }
        }
    }
}