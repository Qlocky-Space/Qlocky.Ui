import QtQuick

import Ui

/**
 * Generic wheel picker showing a single column of entries.
 * The centered entry is the selected one, its neighbours are faded out.
 *
 * Usage:
 *   QPicker {
 *       model: ["A", "B", "C"]           // strings, numbers or objects (see textRole)
 *       currentIndex: 1
 *       onSelected: function (index) { ... }
 *   }
 *
 * Multiple pickers can be combined side by side to build compound
 * pickers, see QTimePicker.
 */
Item {
    id: root

    /**
     * Array of entries. Entries may be strings / numbers or objects,
     * in which case textRole names the property to display.
     */
    property var model: []
    property string textRole: ""

    /**
     * Index of the selected entry within model.
     */
    property int currentIndex: 0

    /**
     * If true, the wheel wraps around (e.g. 23 -> 0 for hours).
     */
    property bool cyclic: false

    /**
     * Number of rows visible at once. Should be odd so the selection is centered.
     */
    property int visibleRows: 5

    /**
     * Number of model copies used to emulate an endless wheel when cyclic.
     */
    property int repetitions: 5

    property int horizontalAlignment: Text.AlignHCenter
    property real textMargin: 0

    readonly property real rowHeight: height / visibleRows
    readonly property int count: model ? model.length : 0

    property real fontPixelSize: Math.min(0.5 * width, rowHeight)

    /**
     * Emitted when the user changed the selection (scroll or tap).
     * Not emitted for programmatic changes of currentIndex.
     */
    signal selected(int index)

    implicitWidth: 200
    implicitHeight: 300

    clip: true

    function textAt(index) {
        if (index < 0 || index >= root.count) {
            return "";
        }
        const entry = root.model[index];
        return root.textRole.length > 0 ? String(entry[root.textRole]) : String(entry);
    }

    // Index of the logical entry inside the wheel, centered in the middle repetition when cyclic
    function _viewIndexOf(index) {
        return root.cyclic ? Math.floor(root.repetitions / 2) * root.count + index : index;
    }

    function _positionAt(index) {
        if (root.count === 0) {
            return;
        }
        const clamped = Math.max(0, Math.min(index, root.count - 1));
        const viewIndex = root._viewIndexOf(clamped);
        view.currentIndex = viewIndex;
        view.positionViewAtIndex(viewIndex, ListView.Center);
    }

    function _commit() {
        if (root.count === 0 || view.currentIndex < 0) {
            return;
        }
        const index = view.currentIndex % root.count;

        // Jump back to the middle repetition so the wheel never reaches its end
        if (root.cyclic && view.currentIndex !== root._viewIndexOf(index)) {
            root._positionAt(index);
        }

        if (index !== root.currentIndex) {
            root._internalChange = true;
            root.currentIndex = index;
            root._internalChange = false;
            root.selected(index);
        }
    }

    property bool _internalChange: false

    onCurrentIndexChanged: {
        if (!root._internalChange) {
            root._positionAt(root.currentIndex);
        }
    }

    onCountChanged: Qt.callLater(root._positionAt, root.currentIndex)
    onHeightChanged: Qt.callLater(root._positionAt, root.currentIndex)
    Component.onCompleted: root._positionAt(root.currentIndex)

    ListView {
        id: view

        anchors.fill: parent

        model: root.cyclic ? root.count * root.repetitions : root.count

        snapMode: ListView.SnapToItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        preferredHighlightBegin: (height - root.rowHeight) / 2
        preferredHighlightEnd: (height + root.rowHeight) / 2
        highlightMoveDuration: 150
        boundsBehavior: Flickable.StopAtBounds

        delegate: Item {
            id: delegateItem

            required property int index

            width: view.width
            height: root.rowHeight

            QLabel {
                anchors.fill: parent
                anchors.leftMargin: root.textMargin
                anchors.rightMargin: root.textMargin

                text: root.textAt(delegateItem.index % root.count)
                horizontalAlignment: root.horizontalAlignment
                font.pixelSize: root.fontPixelSize

                opacity: {
                    const diff = Math.abs(view.currentIndex - delegateItem.index);
                    if (diff === 0) {
                        return 1;
                    }
                    return diff < 2 ? 0.4 : 0.2;
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentIndex = delegateItem.index;
                    root._commit();
                }
            }
        }

        onMovementEnded: root._commit()
    }
}
