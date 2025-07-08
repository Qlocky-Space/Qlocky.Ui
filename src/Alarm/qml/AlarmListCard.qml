import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Widget
import Ui

Widget {

    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.backgroundTertiary

        radius: 30
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            QLabel {
                text: "New Alarm"

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            }

            QButton {
                image: "\u002b"
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                height: 80
                width: 80

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
