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

    // TODO Move model to viewmodel where a module itself
    // could register its own cards.
    ListModel {
        id: loaderModel
        ListElement {
            source: "qrc:/qt/qml/Weather/qml/WeatherCard.qml"
            row: 0
            rowSpan: 2
            column: 0
            columnSpan: 2
        }
        ListElement {
            source: "qrc:/qt/qml/Weather/qml/WeatherPredictionCard.qml"
            row: 2
            rowSpan: 1
            column: 0
            columnSpan: 1
        }
        ListElement {
            source: "qrc:/qt/qml/Alarm/qml/ClockCard.qml"
            row: 0
            rowSpan: 2
            column: 2
            columnSpan: 3
        }
        ListElement {
            source: "qrc:/qt/qml/Radio/qml/RadioCard.qml"
            row: 2
            rowSpan: 1
            column: 2
            columnSpan: 3
        }
    }

    Repeater {
        model: loaderModel

        Loader {
            source: model.source

            Layout.row: model.row
            Layout.rowSpan: model.rowSpan
            Layout.column: model.column
            Layout.columnSpan: model.columnSpan
        }
    }
}
