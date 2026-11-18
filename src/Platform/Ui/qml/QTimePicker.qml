import QtQuick

import Ui

/**
 * Time picker consisting of an hour and a minute QPicker wheel.
 * time is given in seconds since midnight.
 */
Item {
    id: root

    signal clicked(int time)

    property int interval: 1 // 30 20 15 10 5 2 1 minutes
    property int time
    property int rows: 5

    readonly property var hours: Array.from({ length: 24 }, (_, i) => i)
    readonly property var minutes: Array.from({ length: Math.floor(60 / interval) }, (_, i) => ('0' + i * interval).slice(-2))

    width: 200
    height: 300

    clip: true

    function syncFromTime() {
        hourPicker.currentIndex = Math.floor(root.time / 3600) % 24;
        minutePicker.currentIndex = Math.floor((root.time % 3600) / 60 / root.interval);
    }

    function get() {
        return hourPicker.currentIndex * 3600 + minutePicker.currentIndex * root.interval * 60;
    }

    onTimeChanged: syncFromTime()
    Component.onCompleted: syncFromTime()

    Row {
        anchors.fill: parent

        QPicker {
            id: hourPicker
            width: root.width / 2
            height: root.height

            model: root.hours
            cyclic: true
            visibleRows: root.rows
            horizontalAlignment: Text.AlignRight
            textMargin: 50

            onSelected: root.clicked(root.get())
        }

        QPicker {
            id: minutePicker
            width: root.width / 2
            height: root.height

            model: root.minutes
            cyclic: true
            visibleRows: root.rows
            horizontalAlignment: Text.AlignLeft

            onSelected: root.clicked(root.get())
        }
    }

    QLabel {
        text: ':'
        font.pixelSize: Math.min(0.5 * root.width / 2, root.height / root.rows)
        anchors.verticalCenter: parent.verticalCenter
        x: root.width / 2 - 25
    }
}
