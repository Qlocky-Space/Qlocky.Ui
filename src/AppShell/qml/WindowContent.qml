import QtQuick
import QtQuick.Layouts

import Widget

WidgetLayout {
    // Columns
    columns: 5
    columnSpacing: 30
    // Row
    rows: 3
    rowSpacing: 30
    // Anchors
    anchors.fill: parent
    anchors.margins: 20

    Repeater {
        model: WidgetListViewModel

        Loader {
            source: model.source
            Layout.row: model.row
            Layout.rowSpan: model.rowSpan
            Layout.column: model.column
            Layout.columnSpan: model.columnSpan
        }
    }
}
