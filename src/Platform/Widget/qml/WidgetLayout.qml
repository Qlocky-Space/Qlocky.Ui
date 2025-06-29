import QtQuick
import QtQuick.Layouts

Item {
    id: layout

    property int columns: 2
    property int rows: 2
    property int columnSpacing: 20
    property int rowSpacing: 20

    onChildrenChanged: updatePreferredSizes()
    onWidthChanged: updatePreferredSizes()
    onHeightChanged: updatePreferredSizes()
    onColumnsChanged: updatePreferredSizes()
    onRowsChanged: updatePreferredSizes()

    function updatePreferredSizes() {
        if(layout.children.length === 0) {
            return
        }

        var cellWidth = layout.width / columns - (columnSpacing / columns);
        var cellHeight = layout.height / rows - (rowSpacing / rows);
        for(var i=0; i < layout.children.length; ++i) {
            var obj = layout.children[i]

            var c = obj.Layout.column
            var r = obj.Layout.row
            var cs = obj.Layout.columnSpan
            var rs = obj.Layout.rowSpan

            obj.x = c * cellWidth + columnSpacing
            obj.y = r * cellHeight + rowSpacing
            obj.height = rs * cellHeight - rowSpacing
            obj.width = cs * cellWidth - columnSpacing
        }

    }
}


