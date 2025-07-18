import QtQuick

import Ui

/**
 * https://www.ics.com/blog/creating-qml-controls-scratch-timepicker
 */
Item {
    id: root

    signal clicked(date date);

    property int interval: 1 // 30 20 15 10 5 2 1 minutes
    property date date

    width: 200
    height: 300

    clip: true

    onDateChanged: function() {
        delayTimer.start()
    }

    Timer {id: delayTimer;  interval: 20;  onTriggered: set(root.date)}

    property int rows:        5
    property int repetitions: 5

    Row {
        Repeater {
            id: repeater

            model: [ 24 * repetitions, 60 / interval * repetitions ]

            delegate: ListView {
                id: view

                property int column: index

                width: root.width / 2
                height: root.height
                snapMode: ListView.SnapToItem

                model: modelData

                delegate: Item {
                    width: root.width / 2
                    height: root.height / rows

                    QLabel {
                        text: view.get(index)

                        font.pixelSize: Math.min(0.5 * parent.width, parent.height)
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: column == 0 ? parent.right : undefined
                        anchors.left:  column == 1 ? parent.left  : undefined
                        anchors.rightMargin: 50

                        opacity: {
                            if (view.currentIndex === index) {
                                return 1;
                            }

                            var diff = Math.abs(view.currentIndex - index)
                            return diff < 2 ? 0.4 : 0.2;
                        }
                    }
                }

                onMovementEnded: {select(view);  timer.restart()}
                onFlickEnded:    {select(view);  timer.restart()}
                Timer {id: timer;  interval: 1;  onTriggered: clicked(root.get())}

                function get(index) {
                         if(column == 0)  return index % 24                            // hour
                    else if(column == 1)  return ('0' + (index * interval) % 60).slice(-2) // minute
                }
            }
        }
    }

    QLabel {
        text: ':'
        font.pixelSize: Math.min(0.5 * root.width / 2, root.height / rows)
        anchors.verticalCenter: parent.verticalCenter
        x: root.width / 2 - 25
    }

    function set(date) {
        if (repeater.count < 2 || !repeater.itemAt(0) || !repeater.itemAt(1)) {
            console.warn("QTimePicker: Not enough items in repeater to set time");
            return;
        }

        repeater.itemAt(0).positionViewAtIndex(24            * (repetitions - 1) / 2 + date.getHours(), ListView.Center)
        repeater.itemAt(1).positionViewAtIndex(60 / interval * (repetitions - 1) / 2 + date.getMinutes() / interval, ListView.Center)

        for(var column = 0; column < repeater.count; column++) {
            select(repeater.itemAt(column))
        }
    }

    function select(view) {
        view.currentIndex = view.indexAt(0, view.contentY + 0.5 * view.height)
    }

    function get() {
        var newDate = root.date

        newDate.setHours(repeater.itemAt(0).get(repeater.itemAt(0).currentIndex));
        newDate.setMinutes(repeater.itemAt(1).get(repeater.itemAt(1).currentIndex));

        return newDate
    }
}