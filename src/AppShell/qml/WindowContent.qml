import QtQuick
import QtQuick.Layouts

import "Demo"

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

    // TODO Move to Weather Widget
    WeatherCard {}
    WeatherPredictionCard {}

    Card {
        cardColor: "#202226"

        Layout.row: 2
        Layout.rowSpan: 1
        Layout.column: 1
        Layout.columnSpan: 1
    }

    // TODO Move to Alarm Widget
    ClockCard {}
    RadioCard {}
}
