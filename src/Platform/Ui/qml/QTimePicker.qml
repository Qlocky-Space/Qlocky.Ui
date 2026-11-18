import QtQuick

import Ui

/**
 * Time picker consisting of an hour and a minute QPicker wheel.
 * In 12 hour format an additional AM/PM wheel is shown.
 * time is given in seconds since midnight, independent of the format.
 */
Item {
    id: root

    signal clicked(int time)

    property int interval: 1 // 30 20 15 10 5 2 1 minutes
    property int time
    property int rows: 5

    /**
     * True shows hours 0..23, false shows hours 12, 1..11 plus an AM/PM wheel.
     */
    property bool use24HourFormat: true

    readonly property var hours: root.use24HourFormat ? Array.from({
        length: 24
    }, (_, i) => i) : Array.from({
        length: 12
    }, (_, i) => i === 0 ? 12 : i)
    readonly property var minutes: Array.from({
        length: Math.floor(60 / interval)
    }, (_, i) => ('0' + i * interval).slice(-2))

    // Some locales provide no AM/PM designators, fall back to the english ones
    readonly property var periods: [Qt.locale().amText.length > 0 ? Qt.locale().amText : "AM", Qt.locale().pmText.length > 0 ? Qt.locale().pmText : "PM"]

    // Hour index before the latest user selection, needed to detect the 11 <-> 12 crossing
    property int _lastHourIndex: 0

    width: 200
    height: 300

    clip: true

    function syncFromTime() {
        if (root.use24HourFormat) {
            hourPicker.currentIndex = Math.floor(root.time / 3600) % 24;
        } else {
            const hour24 = Math.floor(root.time / 3600) % 24;
            // Index 0 shows "12", so hour24 % 12 is directly the wheel index (0 -> 12 AM, 12 -> 12 PM)
            hourPicker.currentIndex = hour24 % 12;
            periodPicker.currentIndex = hour24 >= 12 ? 1 : 0;
        }
        minutePicker.currentIndex = Math.floor((root.time % 3600) / 60 / root.interval);
        root._lastHourIndex = hourPicker.currentIndex;
    }

    function get() {
        if (root.use24HourFormat) {
            return hourPicker.currentIndex * 3600 + minutePicker.currentIndex * root.interval * 60;
        } else {
            // PM adds a fixed offset of 12 hours (AM index 0, PM index 1)
            return (hourPicker.currentIndex + 12 * periodPicker.currentIndex) * 3600 + minutePicker.currentIndex * root.interval * 60;
        }
    }

    /**
     * Returns true if moving the 12 hour wheel from oldIndex to newIndex passed
     * the boundary between index 11 ("11") and index 0 ("12").
     * QPicker only reports the final index, so the shorter way around the wheel is assumed.
     */
    function _crossedNoonOrMidnight(oldIndex, newIndex) {
        const forwardSteps = (newIndex - oldIndex + 12) % 12;
        if (forwardSteps === 0) {
            return false;
        }
        if (forwardSteps <= 6) {
            return newIndex < oldIndex; // moved forward and wrapped 11 -> 12
        }
        return newIndex > oldIndex; // moved backward and wrapped 12 -> 11
    }

    function _onHourSelected(index) {
        if (!root.use24HourFormat && root._crossedNoonOrMidnight(root._lastHourIndex, index)) {
            periodPicker.currentIndex = 1 - periodPicker.currentIndex;
        }
        root._lastHourIndex = index;
        root.clicked(root.get());
    }

    onTimeChanged: syncFromTime()
    onUse24HourFormatChanged: syncFromTime()
    Component.onCompleted: syncFromTime()

    Row {
        anchors.fill: parent

        QPicker {
            id: hourPicker
            width: root.use24HourFormat ? root.width / 2 : root.width * 0.4
            height: root.height

            model: root.hours
            cyclic: true
            visibleRows: root.rows
            horizontalAlignment: Text.AlignRight
            textMargin: 50

            onSelected: function (index) {
                root._onHourSelected(index);
            }
        }

        QPicker {
            id: minutePicker
            width: hourPicker.width
            height: root.height

            model: root.minutes
            cyclic: true
            visibleRows: root.rows
            horizontalAlignment: Text.AlignLeft

            onSelected: root.clicked(root.get())
        }

        QPicker {
            id: periodPicker
            visible: !root.use24HourFormat
            width: root.width - hourPicker.width - minutePicker.width
            height: root.height

            model: root.periods
            cyclic: false
            visibleRows: root.rows
            horizontalAlignment: Text.AlignLeft
            fontPixelSize: minutePicker.fontPixelSize * 0.6

            onSelected: root.clicked(root.get())
        }
    }

    QLabel {
        text: ':'
        font.pixelSize: Math.min(0.5 * hourPicker.width, root.height / root.rows)
        anchors.verticalCenter: parent.verticalCenter
        x: hourPicker.width - 25
    }
}
