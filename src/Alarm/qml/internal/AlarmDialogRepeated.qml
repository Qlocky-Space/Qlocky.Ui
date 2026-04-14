import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import Ui

Item {
    required property var alarm

    signal done()

    function confirmSelection() {
        done();
    }

    implicitWidth: content.implicitWidth
    implicitHeight: content.implicitHeight

    // Example content, replace with your actual repeat UI
    Column {
        id: content
        anchors.fill: parent
        spacing: 20

        Repeater {

            model: [
                { label: qsTr("Mon"), value: DayOfWeekViewModel.Monday },
                { label: qsTr("Tue"), value: DayOfWeekViewModel.Tuesday },
                { label: qsTr("Wed"), value: DayOfWeekViewModel.Wednesday },
                { label: qsTr("Thu"), value: DayOfWeekViewModel.Thursday },
                { label: qsTr("Fri"), value: DayOfWeekViewModel.Friday },
                { label: qsTr("Sat"), value: DayOfWeekViewModel.Saturday },
                { label: qsTr("Sun"), value: DayOfWeekViewModel.Sunday }
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

    }
}