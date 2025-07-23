import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    required property var alarm

    signal done()

    implicitWidth: content.implicitWidth
    implicitHeight: content.implicitHeight

    // Example content, replace with your actual repeat UI
    Column {
        id: content
        anchors.fill: parent
        spacing: 20

        Repeater {

            model: [
                { label: qsTr("Mon"), value: DayOfWeek.Monday },
                { label: qsTr("Tue"), value: DayOfWeek.Tuesday },
                { label: qsTr("Wed"), value: DayOfWeek.Wednesday },
                { label: qsTr("Thu"), value: DayOfWeek.Thursday },
                { label: qsTr("Fri"), value: DayOfWeek.Friday },
                { label: qsTr("Sat"), value: DayOfWeek.Saturday },
                { label: qsTr("Sun"), value: DayOfWeek.Sunday }
            ]

            delegate: RowLayout {
                spacing: 40
                Layout.fillWidth: true

                QLabel {
                    text: modelData.label

                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    Layout.preferredWidth: 200
                }

                QToggleButton {
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                    checked: alarm.daysOfWeek & modelData.value
                    onToggled: function(state) {
                        alarm.daysOfWeek = state
                            ? alarm.daysOfWeek | modelData.value
                            : alarm.daysOfWeek & ~modelData.value
                    }
                }
            }
        }

        QButton {
            text: qsTr("Return")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                done()
            }
        }
    }
}