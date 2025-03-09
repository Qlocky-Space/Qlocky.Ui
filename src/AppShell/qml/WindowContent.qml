import QtQuick
import QtQuick.Layouts

Item {
    id: root

    GridLayout {
        // Columns
        columns: 4
        columnSpacing: 20
        // Row
        rows: 1
        rowSpacing: 20
        // Anchors
        anchors.fill: parent
        anchors.margins: 20

        children: [
            Card {
                id: test1
                rows: 2
                columns: 2
                cardColor: "#202226"

                Layout.columnSpan: 1
                Layout.column: 2
                Layout.rowSpan: 1
                Layout.row: 1
            },
            Card {
                id: test2
                rows: 1
                columns: 1
                cardColor: "red"

                Layout.columnSpan: 2
                Layout.column: 2
                Layout.rowSpan: 1
                Layout.row: 2
            }
        ]
    }
}
