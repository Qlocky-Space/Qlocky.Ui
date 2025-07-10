import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Widget
import Ui

Widget {
    id: widget

    color: ThemeManager.theme.backgroundTertiary

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            id: header
            Layout.fillWidth: true
            Layout.margins: 16

            QLabel {
                id: title
                text: "New Alarm"
                Layout.fillWidth: true
            }

            QButton {
                image: "\u002b"
                height: 48
                width: 48

                onClicked: {
                    CommandExecutor.dispatch("nav-to", {
                        "uri": "qlocky://newAlarmDialog?text=Custom Close Text"
                    });
                }
            }
        }

        AlarmList {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
