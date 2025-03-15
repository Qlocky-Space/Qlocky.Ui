import QtQuick
import QtQuick.Layouts

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

    Card {
        cardColor: "#202226"

        Layout.row: 0
        Layout.rowSpan: 2
        Layout.column: 0
        Layout.columnSpan: 2
    }

    Card {
        cardColor: "#202226"

        Layout.row: 2
        Layout.rowSpan: 1
        Layout.column: 0
        Layout.columnSpan: 1
    }

    Card {
        cardColor: "#202226"

        Layout.row: 2
        Layout.rowSpan: 1
        Layout.column: 1
        Layout.columnSpan: 1
    }


    Card {
        cardColor: "#202226"

        Layout.row: 0
        Layout.rowSpan: 2
        Layout.column: 2
        Layout.columnSpan: 3
    }

    Card {
        cardColor: "#202226"

        Layout.row: 2
        Layout.rowSpan: 1
        Layout.column: 2
        Layout.columnSpan: 3
    }


}
